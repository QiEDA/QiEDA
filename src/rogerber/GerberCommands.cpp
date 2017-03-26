//
// Created by mroszko on 3/23/2017.
//

#include "rogerber/Gerber.hpp"
#include "fmt/format.h"

using namespace rogerber;


std::string ModeStatement::Dump()
{
	return "Type: Mode";
}

std::string OperationStatement::Dump()
{
	return fmt::format("[Operation]RawX={0},RawY={1},RawI={2},RawJ={3}", rawX_, rawY_, rawI_, rawJ_);
}


std::string FormatStatement::Dump()
{
	return fmt::format("[Format]CoordinateNotation={0},xIntegerPositions={1},xDecimalPositions={2},yIntegerPositions={3},yDecimalPositions={4},zeroOmission={5}",
						(int)coordinateNotation_,
					   xIntegerPositions_,
					   xDecimalPositions_,
					   yIntegerPositions_,
					   yDecimalPositions_,
					   (int)zeroOmission_);
}

std::string ApertureDefinition::Dump()
{
	return fmt::format("[ApertureDefinition]Number={0}", number_);
}

std::string ApertureSelection::Dump()
{
	return fmt::format("[ApertureSelection]Aperature={0}", aperture_);
}

std::string UnitCommand::Dump()
{
	return fmt::format("[Unit]Units={0}", (int)units_);
}

std::string QuadrantMode::Dump()
{
	return fmt::format("[QuadrantMode]State={0}", (int)mode_);
}

std::string InterpolationMode::Dump()
{
	return fmt::format("[InterpolationMode]State={0}", (int)mode_);
}

std::string LegacyUnitMillimetersCommand::Dump()
{
	return "[LegacySetMillimeters]";
}

std::string LegacyUnitInchCommand::Dump()
{
	return "[LegacySetInches]";
}

std::string RegionStatement::Dump()
{
	return fmt::format("[RegionStatement]Start=",start_);
}