#ifndef GERBER_HPP
#define GERBER_HPP

#include <string>
#include <vector>
#include <queue>
#include "qigerber/qigerber.hpp"

namespace qigerber {
	enum GerberCommandType {
		Operation,
		Mode
	};
	
	class QIGERBER_EXPORT GerberCommand {
		GerberCommandType Type;
	public:
		GerberCommand( GerberCommandType type )
		{
			Type = type;
		}
	};
	
	/*
	 *	Operations can exist in two formats
	 * = [X<Number>][Y<Number>][I<Number>][J<Number>]D01*, where the D-code is explicit
	 * and in the case of D1 where following statements assume the previous D01
	 *
	 */
	class QIGERBER_EXPORT OperationStatement : public GerberCommand {
	public:
		float x;	//x coord
		float y;	//y coord
		float i;	//distance or offset in x/y, circular interpolate only
		float j;	
		
		OperationStatement() : GerberCommand(GerberCommandType::Operation)
		{
		}
	};
	
	class QIGERBER_EXPORT ModeStatement : public GerberCommand {
	public:
		ModeStatement() : GerberCommand(GerberCommandType::Mode)
		{
		}
	};
	
	/*
	 * D## codes are known as operation codes
	 */
	enum OperationType
	{
		Interpolate,	//D01
		Move,			//D02
		Flash			//D03
	};
	
	enum ModeType {
		LinearInterpolation = 1,	//G01
		ClockwiseCircularInterpolation = 2,	//G02
		CounterclockwiseCircularInterpolation = 3, //G03
		
		SingleQuadrantMode = 74, //G74
		MultiQuadrantMode = 75, //G75
		
		RegionOn = 36,	//G36
		RegionOff = 37, //G37
	};

	/*
	 * \brief Loads a gerber from file and creates an in memory stream of commands
	 *
	 *	The gerber format is sort of a "on the fly" system where machines are supposed to execute
	 *  instructions on the fly.
	 *  This class creates the abstraction to create the stream of instructions so that
	 *  other code layers may then use to convert to 2d shapes (or other purposes).
	 *
	 */
	class QIGERBER_EXPORT Gerber {
	public:
		Gerber();
		bool Load(std::string path);
        void Parse(std::string& file);
	private:
        void parseExtended(const std::string& file, std::string::const_iterator& it);
        void parseExtendedBlocks(std::queue<std::string>& blocks);
        void parseCommand();
		
		std::vector<GerberCommand*> commands;
	};
}

#endif