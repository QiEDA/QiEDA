#include <fstream>
#include <sstream>
#include <regex>
#include "rogerber/Gerber.hpp"
#include "rogerber/GerberException.hpp"

using namespace rogerber;

 
Gerber::Gerber() {
}

bool Gerber::Load(std::string path) {
	std::ifstream file(path, std::fstream::in);
	
	if( file.is_open() ) {
		//Let's read the entire file to memory as we want to parse char by char
		std::ostringstream contentsBuffer;
		contentsBuffer << file.rdbuf();
		file.close();
	
		std::string contents = contentsBuffer.str();
        Parse(contents);
	}
	else {
		return false;
	}
	
	return true;
}

void Gerber::Parse(std::string& file)
{
    std::string::const_iterator it = file.begin();

    for (; it != file.end(); ++it) {
		bool cont = true;
		switch(*it) {
			case '\n':
			case '\r':
			case '\t':
			case ' ':
				//end of lines/whitespace are ignored in gerbers
				break;
			case '%':
                parseExtended(file, it);
				break;
            default:
                cont = parseCommand(file, it);
				break;
		}

		if(!cont) {
			break;
		}
	}
	
}

std::string Gerber::Dump()
{
	std::stringstream ss;
	for (auto it = commands.begin(); it != commands.end(); ++it) {
		ss << (*it)->Dump() << std::endl;
	}

	return ss.str();
}


bool Gerber::parseCommand(const std::string& file, std::string::const_iterator& it)
{
	size_t startPos = std::distance(file.begin(), it);
	size_t endPos = file.find_first_of('*', startPos);


	if (endPos == std::string::npos)
	{
		throw std::logic_error("malformed gerber, missing block closure");
	}


	std::string block = file.substr(startPos, endPos-startPos);
	std::advance(it, endPos-startPos+1);

	//capture DXX codes blindly because there can be variable number of leading zeros or no leading zeros
	std::regex regexGCode("^G(\\d{1,2})$");
	std::regex regexCurrentAperture("^D(\\d+)$");
	std::regex regexCommand("^((?:[XYIJ][+-]?\\d+){1,4})D?(\\d+)?$");
	std::regex regexXCoord("X([+-]?[\\d\\.]+)");
	std::regex regexYCoord("Y([+-]?[\\d\\.]+)");
	std::regex regexICoord("I([+-]?[\\d\\.]+)");
	std::regex regexJCoord("J([+-]?[\\d\\.]+)");

	std::smatch matches;

	//end of file command
	if(block == "M02") {
		return false;
	}
	else if (std::regex_search(block, matches, regexGCode)) {
		if(matches.size() == 2) {
			int num = std::stoi(matches[1], nullptr);

			GerberCommand* result = nullptr;
			switch(num) {
				case 1:	//linear
				case 2:	//clockwise circular
				case 3:	//counterclockwise circular
					result = new InterpolationMode((GerberInterpolationMode)num);
					break;
				case 74:	//single quad
				case 75:	//multi quad
					result = new QuadrantMode((GerberQuadrantMode)num);
					break;
				case 70:	//
					result = new LegacyUnitInchCommand();
					break;
				case 71:
					result= new LegacyUnitMillimetersCommand();
					break;
				case 36:
					result = new RegionStatement(true);
					break;
				case 37:
					result = new RegionStatement(false);
					break;
				default:
					throw GerberException("Unknown G## code encountered");
			}

			if(result != nullptr)
			{
				commands.push_back(result);
			}
		}
	}
	else if (std::regex_search(block, matches, regexCurrentAperture)) {
		if(matches.size() == 2) {
			int num = std::stoi(matches[1], nullptr);

			if(num >= 10)
			{
				ApertureSelection* ap = new ApertureSelection(num);
				commands.push_back(ap);
			}
			else
			{
				//invalid, aps are only >= 10
			}

		}
	}
	else if (std::regex_search(block, matches, regexCommand)) {
		GerberOperationType type = GerberOperationType::Undefined;

		std::string xCoord;
		std::string yCoord;
		std::string jCoord;
		std::string iCoord;
		if(matches.size() >= 2) {
			std::string coords = matches[1];
			std::smatch coordMatches;

			if (std::regex_search(coords, coordMatches, regexXCoord)) {
				if(coordMatches.size() == 2) {
					xCoord = coordMatches[1];
				}
			}

			if (std::regex_search(coords, coordMatches, regexYCoord)) {
				if(coordMatches.size() == 2) {
					yCoord = coordMatches[1];
				}
			}

			if (std::regex_search(coords, coordMatches, regexJCoord)) {
				if(coordMatches.size() == 2) {
					jCoord = coordMatches[1];
				}
			}

			if (std::regex_search(coords, coordMatches, regexICoord)) {
				if(coordMatches.size() == 2) {
					iCoord = coordMatches[1];
				}
			}
		}

		if(matches.size() >= 3) {
			int dcode = std::stoi(matches[2], nullptr);

			if(dcode <= 3 && dcode >= 1)
			{
				type = (GerberOperationType)dcode;
			}
		}

		OperationStatement* operation = new OperationStatement(type, xCoord, yCoord, jCoord, iCoord);
		commands.push_back(operation);
	}

	return true;
}

void Gerber::parseExtended(const std::string& file, std::string::const_iterator& it)
{
    if( *it != '%' )
    {
        throw std::logic_error("unexpected beginning character for parameter");
    }

    size_t startPos = std::distance(file.begin(), it) + 1;
    size_t extendedEndPos = file.find_first_of('%', startPos);

    if (extendedEndPos == std::string::npos)
    {
        throw std::logic_error("malformed gerber, missing block closure");
    }

    std::queue<std::string> blocks;
    size_t pos = startPos;
    while( pos < extendedEndPos )
    {
        size_t blockEnd = file.find("*",pos);

        if(blockEnd != std::string::npos)
        {
            blocks.push(file.substr(pos, blockEnd-pos));
        }

        pos = blockEnd+1;
    }

    parseExtendedBlocks(blocks);
    std::advance(it, extendedEndPos-startPos+1);
}

//Simple optimization to switch case on the first two string chars
#define BLOCK_NAME(x,y)   ((uint32_t)((((uint32_t)x) << 8) | ((uint32_t)y)))

void Gerber::parseExtendedBlocks(std::queue<std::string>& blocks)
{
    while(blocks.size() > 0)
    {
        auto block = blocks.front();

        switch(BLOCK_NAME(block[0],block[1]))
        {
            case BLOCK_NAME('F','S'):
                parseFormatBlock(block);
                break;
            case BLOCK_NAME('M','O'):
                parseUnitBlock(block);
                break;
            case BLOCK_NAME('A','M'):
                break;
            case BLOCK_NAME('A','D'):
				parseApertureBlock(block);
                break;
            case BLOCK_NAME('L','P'):
                parseLoadPolarityBlock(block);
                break;
            case BLOCK_NAME('I','P'):
                parseImagePolarityBlock(block);
                break;
        }

        blocks.pop();
    }
}

std::vector<std::string> Gerber::splitString(std::string str, char delimiter) {
	std::vector<std::string> internal;
	std::stringstream ss(str);
	std::string tok;

	while(std::getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return internal;
}


void Gerber::parseApertureBlock(std::string& block)
{
	if(block[2] != 'D')
	{
		return;
	}

	int num = 0;
	std::string type = "";

	std::regex ap("^ADD0*(\\d{2,})([A-Za-z_\\$][\\w\\-\\.]*)(?:,((?:X?[\\d.]+)*))?");
	std::smatch apMatch;
	if (std::regex_search(block, apMatch, ap)) {
		if(apMatch.size() >= 4) {
			num = std::stoi(apMatch[1], nullptr);

			type = apMatch[2].str();
		}
	}
	else {
		//invalid format?
	}


	ApertureDefinition* app = nullptr;

	if(type == "C") {
		if(apMatch.size() >= 4)
		{
			float circleDiameter = 0.0f;
			float holeDiameter = 0.0f;
			std::vector<std::string> dims = splitString(apMatch[3],'X');

			//required
			if(dims.size() >= 1)
			{
				circleDiameter = std::stof(dims[0], nullptr);
			}
			else
			{
				throw GerberException("one or more required modifiers of the circle aperture definition are missing");
			}

			//optional
			if(dims.size() >= 2)
			{
				holeDiameter = std::stof(dims[1], nullptr);
			}

			app = new CircleApertureDefinition(num, circleDiameter, holeDiameter);
		}
	} else if( type == "R" || type == "O") {
		if (apMatch.size() >= 4) {
			float xSize = 0.0f;
			float ySize = 0.0f;
			float holeDiam = 0.0f;
			std::vector<std::string> dims = splitString(apMatch[3], 'X');

			//required
			if (dims.size() >= 2) {
				xSize = std::stof(dims[0], nullptr);
				ySize = std::stof(dims[1], nullptr);
			} else {
				throw GerberException(
						"one or more required modifiers of the rectangle/obround aperture definition are missing");
			}

			//optional
			if (dims.size() >= 3) {
				holeDiam = std::stof(dims[2], nullptr);
			}

			if (type == "R") {
				app = new RectangleApertureDefinition(num, xSize, ySize, holeDiam);
			} else if (type == "O") {
				app = new ObroundApertureDefinition(num, xSize, ySize, holeDiam);
			}
		}
	} else if( type == "P" ) {
		if(apMatch.size() >= 4)
		{
			float outerDiam = 0.0f;
			unsigned int numVerts = 0;
			float rotation = 0.0f;
			float holeDiam = 0.0f;
			std::vector<std::string> dims = splitString(apMatch[3],'X');

			//required
			if(dims.size() >= 2)
			{
				outerDiam = std::stof(dims[0], nullptr);
				numVerts = std::stoul(dims[1], nullptr);
			}
			else
			{
				throw GerberException("one or more required modifiers of the poly aperture definition are missing");
			}

			//optional
			if(dims.size() >= 3)
			{
				rotation = std::stof(dims[2], nullptr);
			}

			if(dims.size() >= 4)
			{
				holeDiam = std::stof(dims[3], nullptr);
			}

			app = new PolygonAperatureDefinition(num, outerDiam, numVerts, rotation, holeDiam);
		}
	} else {
		std::vector<std::string> modifiers = splitString(apMatch[3],'X');
		app = new MacroApertureDefinition(num, type, modifiers);
	}

	if(app != nullptr)
	{
		commands.push_back(app);
	}
}

void Gerber::parseLoadPolarityBlock(std::string& block)
{
    switch(block[2])
    {
        case 'C':
            //clear
            break;
        case 'D':
            //dark
            break;
        default:
            //invalid
            break;
    }
}

void Gerber::parseImagePolarityBlock(std::string& block)
{
    if(block.find("IPPOS") != std::string::npos )
    {
        GerberCommand* cmd = new UnitCommand(GerberUnitMode::Millimeters);

        commands.push_back(cmd);
    }
    else if(block.find("IPNEG") != std::string::npos )
    {
        GerberCommand* cmd = new UnitCommand(GerberUnitMode::Inches);

        commands.push_back(cmd);
    }
    else
    {
        //error
    }
}


void Gerber::parseFormatBlock(std::string& block)
{
    GerberZeroOmission zo;
    switch(block[2])
    {
        case 'L':
            zo = GerberZeroOmission::Leading;
            //leading
            break;
        case 'T':
            zo = GerberZeroOmission::Trailing;
            //trailing
            break;
		case 'Z':
			//Leading and Trailing zeros, thank you other CAD software!
			//May as well catch it and barf
			throw GerberException("Non-standard RS274 extension detected for trailing and leading zero coordinate format");
			break;
        default:
            //invalid
			throw GerberException("Unknown format zero omission setting");
            break;
    }

    GerberCoordinateNotation cn;
    switch(block[3])
    {
        case 'A':
            cn = GerberCoordinateNotation::Absolute;
            break;
        case 'I':
            cn = GerberCoordinateNotation::Incremental;
            break;
        default:
            //invalid
            break;
    }

    if(block[4] != 'X')
    {
        //invalid
        return;
    }

    int xIntegerPositions = block[5]  - '0';
    int xDecimalPositions = block[6]  - '0';

    if(block[7] != 'Y')
    {
        //invalid
        return;
    }

    int yIntegerPositions = block[8]  - '0';
    int yDecimalPositions = block[9]  - '0';

    FormatStatement* cmd = new FormatStatement(zo,cn,xIntegerPositions, xDecimalPositions, yIntegerPositions, yDecimalPositions);
    commands.push_back(cmd);
}

void Gerber::parseUnitBlock(std::string& block)
{
    if(block.length() != 4)
    {
        //error
        return;
    }

    if(block.find("MOMM") != std::string::npos )
    {
        GerberCommand* cmd = new UnitCommand(GerberUnitMode::Millimeters);

        commands.push_back(cmd);
    }
    else if(block.find("MOIN") != std::string::npos )
    {
        GerberCommand* cmd = new UnitCommand(GerberUnitMode::Inches);

        commands.push_back(cmd);
    }
    else
    {
        //error
    }
}