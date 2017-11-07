//
// Created by mroszko on 3/25/2017.
//

#ifndef ROEDA_GERBERCOMMANDS_HPP
#define ROEDA_GERBERCOMMANDS_HPP

#include <vector>
#include "rogerber/rogerber.hpp"

namespace rogerber {

enum struct GerberOperationType {
	Undefined = 0,
	/**
	 * Interpoalates from "current point" to the provided coordinate pair in the operation" to create an object
	 */
	Interpolate = 1,
	/**
	 * Moves the current point
	 */
	Move = 2,
	/**
	 * Replicates the current aperature, origin at the given coordinate pair. Results in creation of object
	 */
	Flash = 3
};

enum struct GerberInterpolationMode {
	Linear = 1,
	ArcClockwise = 2,
	ArcCounterClockwise = 3
};

enum struct GerberQuadrantMode {
	Single = 74,
	Multi = 75
};

enum struct GerberCommandType {
	Operation,
	Mode,
	Unit,
	Format,
	ApertureDefinition,
	ApertureMacro,
	AperatureSelection,
	Interpolation,
	Quadrant,
	Region
};

enum struct GerberUnitMode {
	Inches,
	Millimeters,
	Unknown
};

enum struct GerberZeroOmission {
	Leading,
	Trailing
};

enum struct GerberCoordinateNotation {
	Absolute,
	Incremental
};

enum struct GerberAperturePrimitive {
	Circle,
	Rectangle,
	Obround,
	Polygon,
	Macro
};

class ROGERBER_EXPORT GerberCommand {
	GerberCommandType type_;
public:
	GerberCommand( GerberCommandType type )
	{
		type_ = type;
	}

	GerberCommandType GetType() const
	{
		return type_;
	}

	virtual std::string Dump() = 0;
};


class ROGERBER_EXPORT InterpolationMode : public GerberCommand {
public:
	InterpolationMode(GerberInterpolationMode mode) : GerberCommand(GerberCommandType::Interpolation)
	{
			mode_ = mode;
	}

	GerberInterpolationMode GetMode() const
	{
		return mode_;
	}

	std::string Dump() override;
protected:
	GerberInterpolationMode mode_;
};

class ROGERBER_EXPORT QuadrantMode : public GerberCommand {
public:
	QuadrantMode(GerberQuadrantMode mode) : GerberCommand(GerberCommandType::Quadrant)
	{
			mode_ = mode;
	}

	GerberQuadrantMode GetMode() const
	{
		return mode_;
	}

	std::string Dump() override;
protected:
	GerberQuadrantMode mode_;
};

class ROGERBER_EXPORT ApertureDefinition : public GerberCommand {
public:
	ApertureDefinition(unsigned int number, GerberAperturePrimitive primitive) : GerberCommand(GerberCommandType::ApertureDefinition)
	{
		number_ = number;
		primitive_ = primitive;
	}

	std::string Dump() override;

	GerberAperturePrimitive GetPrimitive() const
	{
		return primitive_;
	}

	unsigned int GetNumber() const
	{
		return number_;
	}

protected:
	unsigned int number_;

	GerberAperturePrimitive primitive_;
};


class ROGERBER_EXPORT MacroApertureDefinition : public ApertureDefinition {
public:
	MacroApertureDefinition(int number, std::string macroName, std::vector<std::string>& modifiers) : ApertureDefinition(number, GerberAperturePrimitive::Macro),
																									  modifiers_(modifiers)
	{
		macroName_ = macroName;
	}

private:
	std::string macroName_;
	std::vector<std::string> modifiers_;
};

class ROGERBER_EXPORT CircleApertureDefinition : public ApertureDefinition {
public:
	CircleApertureDefinition(int number, float diameter, float holeDiameter) : ApertureDefinition(number, GerberAperturePrimitive::Circle)
	{
		diameter_ = diameter;
		holeDiameter_ = holeDiameter;
	}

	float GetDiameter() const {
		return diameter_;
	}

	float GetHoleDiameter() const {
		return holeDiameter_;
	}
private:
	float diameter_;
	float holeDiameter_;
};


class ROGERBER_EXPORT PolygonAperatureDefinition : public ApertureDefinition {
public:
	PolygonAperatureDefinition(int number, float outerDiameter, unsigned int numberVerts, float rotationAngle, float holeDiameter) : ApertureDefinition(number, GerberAperturePrimitive::Polygon)
	{
		outerDiameter_ = outerDiameter;
		numberVerts_ = numberVerts;
		rotationAngle_ = rotationAngle;
		holeDiameter_ = holeDiameter;
	}

	float GetOuterDiameter() const {
		return outerDiameter_;
	}

	int GetNumberOfVertices() const {
		return numberVerts_;
	}

	float GetRotationAngle() const {
		return rotationAngle_;
	}

	float GetHoleDiameter() const {
		return holeDiameter_;
	}
private:
	float outerDiameter_;
	unsigned int numberVerts_;
	float rotationAngle_;
	float holeDiameter_;
};

class ROGERBER_EXPORT ObroundApertureDefinition : public ApertureDefinition {
public:
	ObroundApertureDefinition(int number, float xSize, float ySize, float holeDiameter) : ApertureDefinition(number, GerberAperturePrimitive::Obround)
	{
		xSize_ = xSize;
		ySize_ = ySize;
		holeDiameter_ = holeDiameter;
	}

	float GetXSize() const {
		return xSize_;
	}

	float GetYSize() const {
		return ySize_;
	}

	float GetHoleDiameter() const {
		return holeDiameter_;
	}
private:
	float xSize_;
	float ySize_;
	float holeDiameter_;
};

class ROGERBER_EXPORT RectangleApertureDefinition : public ApertureDefinition {
public:
	RectangleApertureDefinition(int number, float xSize, float ySize, float holeDiameter) : ApertureDefinition(number, GerberAperturePrimitive::Rectangle)
	{
		xSize_ = xSize;
		ySize_ = ySize;
		holeDiameter_ = holeDiameter;
	}

	float GetXSize() const {
		return xSize_;
	}

	float GetYSize() const {
		return ySize_;
	}

private:
	float xSize_;
	float ySize_;
	float holeDiameter_;
};

class ROGERBER_EXPORT RegionStatement : public GerberCommand {
public:
	RegionStatement(bool start) : GerberCommand(GerberCommandType::Region)
	{
		start_ = start;
	}

	std::string Dump() override;

	bool IsStart() const
	{
		return start_;
	}

	bool IsStop() const
	{
		return !start_;
	}
private:
	bool start_;
};

/*
 *	Operations can exist in two formats
 * = [X<Number>][Y<Number>][I<Number>][J<Number>]D01*, where the D-code is explicit
 * and in the case of D1 where following statements assume the previous D01
 *
 */
class ROGERBER_EXPORT OperationStatement : public GerberCommand {
public:

OperationStatement(GerberOperationType operation,
		const std::string& rawX, const std::string& rawY,
		const std::string& rawI, const std::string& rawJ )
		: GerberCommand(GerberCommandType::Operation)
	{
		rawX_ = rawX;
		rawY_ = rawY;
		rawI_ = rawI;
		rawJ_ = rawJ;
		operation_ = operation;
	}

	GerberOperationType GetOperationType() const
	{
		return operation_;
	}

	const std::string& GetRawX() const
	{
		return rawX_;
	}

	const std::string& GetRawY() const
	{
		return rawY_;
	}

	const std::string& GetRawI() const
	{
		return rawI_;
	}

	const std::string& GetRawJ() const
	{
		return rawJ_;
	}

	std::string Dump() override;
private:
	GerberOperationType operation_;
	std::string rawX_;
	std::string rawY_;
	std::string rawI_;
	std::string rawJ_;
};

class ROGERBER_EXPORT ModeStatement : public GerberCommand {
public:
ModeStatement() : GerberCommand(GerberCommandType::Mode)
{
}

std::string Dump() override;
};

class ROGERBER_EXPORT FormatStatement : public GerberCommand {
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

	bool IsAbsoluteNotation() const
	{
		return coordinateNotation_ == GerberCoordinateNotation::Absolute;
	}

	bool IsLeadingZeroOmission() const
	{
		return zeroOmission_ == GerberZeroOmission::Leading;
	}

	std::string Dump() override;
private:
	int xIntegerPositions_;
	int xDecimalPositions_;
	int yIntegerPositions_;
	int yDecimalPositions_;
	GerberZeroOmission zeroOmission_;
	GerberCoordinateNotation coordinateNotation_;
};

class ROGERBER_EXPORT ApertureSelection : public GerberCommand {
public:
	ApertureSelection(unsigned int aperture) : GerberCommand(GerberCommandType::AperatureSelection)
	{
		aperture_ = aperture;
	}

	unsigned int GetAperture() const
	{
		return aperture_;
	}

	std::string Dump() override;
private:
	unsigned int aperture_;
};

class ROGERBER_EXPORT UnitCommand : public GerberCommand {
public:
	UnitCommand(GerberUnitMode units) : GerberCommand(GerberCommandType::Unit)
			{
					units_ = units;
			}

	GerberUnitMode GetUnits() const
	{
		return units_;
	}

	std::string Dump() override;
protected:
	GerberUnitMode units_;
};

class ROGERBER_EXPORT LegacyUnitInchCommand : public UnitCommand {
public:
	LegacyUnitInchCommand() : UnitCommand(GerberUnitMode::Inches)
	{
	}

	std::string Dump() override;
};

class ROGERBER_EXPORT LegacyUnitMillimetersCommand : public UnitCommand {
	public:
	LegacyUnitMillimetersCommand() : UnitCommand(GerberUnitMode::Millimeters)
	{
	}

	std::string Dump() override;
};

}

#endif //ROEDA_GERBERCOMMANDS_HPP
