#ifndef GERBER_HPP
#define GERBER_HPP

#include <string>
#include <vector>
#include <queue>
#include "rogerber/rogerber.hpp"
#include "rogerber/GerberCommands.hpp"

namespace rogerber {


/*
 * \brief Loads a gerber from file and creates an in memory stream of commands
 *
 *	The gerber format is sort of a "on the fly" system where machines are supposed to execute
 *  instructions on the fly.
 *  This class creates the abstraction to create the stream of instructions so that
 *  other code layers may then use to convert to 2d shapes (or other purposes).
 *
 */
class ROGERBER_EXPORT Gerber {
public:
	Gerber();
	bool Load(std::string path);
	void Parse(std::string& file);
	std::string Dump();

	const std::vector<GerberCommand*>& GetCommands() const
	{
		return commands;
	}
private:
	std::vector<std::string> splitString(std::string str, char delimiter);
	void parseExtended(const std::string& file, std::string::const_iterator& it);
	void parseExtendedBlocks(std::queue<std::string>& blocks);
	bool parseCommand(const std::string& file, std::string::const_iterator& it);
	void parseFormatBlock(std::string& block);
	void parseUnitBlock(std::string& block);
	void parseImagePolarityBlock(std::string& block);
	void parseLoadPolarityBlock(std::string& block);
	void parseApertureBlock(std::string& block);


	std::vector<GerberCommand*> commands;
};

}

#endif