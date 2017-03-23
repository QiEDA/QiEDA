#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <regex>
#include "rogerber/Gerber.hpp"

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
                parseCommand(file, it);
				break;
		}
	}
	
}


void Gerber::parseCommand(const std::string& file, std::string::const_iterator& it)
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
	std::regex regexCurrentAperture("^D(\\d+)$");
	std::regex regexCommand("^((?:[XYIJ][+-]?\\d+){1,4})D?(\\d+)?$");
	std::regex regexXCoord("X([+-]?[\\d\\.]+)");
	std::regex regexYCoord("Y([+-]?[\\d\\.]+)");
	std::regex regexICoord("I([+-]?[\\d\\.]+)");
	std::regex regexJCoord("J([+-]?[\\d\\.]+)");

	std::smatch matches;
	if (std::regex_search(block, matches, regexCurrentAperture)) {
		int c = matches.size();
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
	char type = 'A';

	std::regex ap("^ADD0*(\\d{2,})([A-Za-z_\\$][\\w\\-\\.]*)(?:,((?:X?[\\d.]+)*))?");
	std::smatch apMatch;
	if (std::regex_search(block, apMatch, ap)) {
		int matches = apMatch.size();
		if(apMatch.size() >= 4) {
			num = std::stoi(apMatch[1], nullptr);
			type = apMatch[2].str()[0];
		}
	}
	else {
		//invalid format?
	}

	ApertureDefinition* app = nullptr;

	switch(type) {
		case 'C': {
			if(apMatch.size() >= 4)
			{
				float circleDiameter = 0.0f;
				float holeDiameter = 0.0f;
				std::vector<std::string> dims = splitString(apMatch[3],'X');

				if(dims.size() >= 1)
				{
					circleDiameter = std::stof(dims[0], nullptr);
				}

				if(dims.size() >= 2)
				{
					holeDiameter = std::stof(dims[1], nullptr);
				}

				app = new CircleApertureDefinition(num, circleDiameter, holeDiameter);
			}
		}
			break;
		case 'R':
			break;
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
        default:
            //invalid
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