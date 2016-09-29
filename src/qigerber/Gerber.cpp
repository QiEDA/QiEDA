#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include "qigerber/Gerber.hpp"

using namespace qigerber;

 
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
                parseCommand();
				break;
		}
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


void Gerber::parseCommand()
{

}