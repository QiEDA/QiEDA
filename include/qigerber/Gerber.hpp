#ifndef GERBER_HPP
#define GERBER_HPP

#include <string>
#include <vector>
#include <queue>
#include "qigerber/qigerber.hpp"

namespace qigerber {
enum GerberCommandType {
	Operation,
	Mode,
	Unit,
	Format
};

enum GerberUnitMode {
	Inches,
	Millimeters
};

enum GerberZeroOmission {
	Leading,
	Trailing
};

enum GerberCoordinateNotation {
	Absolute,
	Incremental
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

class QIGERBER_EXPORT FormatStatement : public GerberCommand {
public:
	FormatStatement(GerberZeroOmission zeroOmission, GerberCoordinateNotation coordinateNotation,
					int xIntegerPos, int xDecimalPos, int yIntegerPos, int yDecimalPos) : GerberCommand(GerberCommandType::Format)
	{
		coordinateNotation_ = coordinateNotation;
		xIntegerPositions_ = xIntegerPos;
		xDecimalPositions_ = xDecimalPos;
		yIntegerPositions_ = yIntegerPos;
		yDecimalPositions_ = yDecimalPos;
		zeroOmission_ = zeroOmission;
	}

	int GetXIntegerPositions() const
	{
		return xIntegerPositions_;
	}

	int GetXDecimalPositions() const
	{
		return xDecimalPositions_;
	}

	int GetYIntegerPositions() const
	{
		return yIntegerPositions_;
	}

	int GetYDecimalPositions() const
	{
		return yDecimalPositions_;
	}
private:
	int xIntegerPositions_;
	int xDecimalPositions_;
	int yIntegerPositions_;
	int yDecimalPositions_;
	GerberZeroOmission zeroOmission_;
	GerberCoordinateNotation coordinateNotation_;
};

class QIGERBER_EXPORT UnitCommand : public GerberCommand {
public:
	UnitCommand(GerberUnitMode units) : GerberCommand(GerberCommandType::Unit)
	{
		units_ = units;
	}

	GerberUnitMode GetUnits() const
	{
		return units_;
	}
private:
	GerberUnitMode units_;
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
	void parseFormatBlock(std::string& block);
	void parseUnitBlock(std::string& block);
	void parseImagePolarityBlock(std::string& block);
	void parseLoadPolarityBlock(std::string& block);

	std::vector<GerberCommand*> commands;
};
}

#endif