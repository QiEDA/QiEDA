//
// Created by mroszko on 3/24/2017.
//

#include <cmath>
#include <iostream>
#include "rogerber/GerberExecutor.hpp"
#include "fmt/format.h"
#include "fmt/ostream.h"

using namespace rogerber;

#define ROGERBER_DEBUG

#define IS_APERTURE_LOADED() (currentAperture_ > 0)


void GerberExecutor::EmitLine(unsigned int aperture,
		                      GerberCoordinate& start,
							  GerberCoordinate& stop,
							  int width)
{
#ifdef ROGERBER_DEBUG
	std::cout << fmt::format("[Executor][Emit][Line]aperature={0},start.x={1},start.y={2},stop.x={3},stop.y={4},width={5}",
									aperture, start.X, start.Y, stop.X, stop.Y, width) << std::endl;
#endif

}

void GerberExecutor::EmitArc(unsigned int aperture,
							  GerberCoordinate& start,
							  GerberCoordinate& stop,
							  GerberCoordinate& center,
							  bool clockwise,
							  bool multiQuadrant,
							  int width)
{

}

void GerberExecutor::processOperationInsideRegion(OperationStatement* op, GerberCoordinate& xyCoordinate)
{
	switch(op->GetOperationType())
	{
		case GerberOperationType::Move:
			break;
		case GerberOperationType::Interpolate:
			break;
		case GerberOperationType::Flash:
			throw GerberException("Flash command not allow inside a region");	//per Gerber 4.14.1 Region Overview
		default:
			throw GerberException("Unknown operation type");
	}
}

ApertureDefinition* GerberExecutor::getApertureDefinition(unsigned int aperture)
{
	if(aperture == 0)
	{
		return nullptr;
	}

	auto search = currentApertures_.find(aperture);

	if(search != currentApertures_.end())
	{
		return search->second;
	}

	return nullptr;
}

void GerberExecutor::registerAperture(ApertureDefinition* def)
{
	currentApertures_[def->GetNumber()] = def;
}

void GerberExecutor::processOperation(OperationStatement* op, GerberCoordinate& operationCoordinate)
{
	switch(op->GetOperationType())
	{
		case GerberOperationType::Interpolate:
			{
#ifdef ROGERBER_DEBUG
			std::cout << fmt::format("[Executor][Operation][Interpolate]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
#endif
				exposureOn_ = true;

				if (!IS_APERTURE_LOADED()) {
					throw GerberException("No aperture loaded");
				}

				auto properties = getApertureDefinition(currentAperture_);

				if(properties == nullptr)
				{
					throw GerberException("Could not find aperture definition when trying to use it");
				}

				switch (interpolationMode_) {
					case GerberInterpolationMode::Linear:
						EmitLine(currentAperture_, previousPosition_, operationCoordinate, 1);
						break;
					case GerberInterpolationMode::ArcClockwise:
					case GerberInterpolationMode::ArcCounterClockwise:
						{
							GerberCoordinate center;
							center.X = convertICoordinate(op->GetRawI());
							center.Y = convertJCoordinate(op->GetRawJ());
							//now since the I and J are relative, add the X and Y to it
							center.X += operationCoordinate.X;
							center.Y += operationCoordinate.Y;

							EmitArc(currentAperture_, previousPosition_, operationCoordinate,
									center, (interpolationMode_ == GerberInterpolationMode::ArcClockwise),
									quadrantMode_ == GerberQuadrantMode::Multi, 1);
						}
						break;
				}

				previousPosition_ = operationCoordinate;
			}
			break;
		case GerberOperationType::Move:
			//moving causes nothing to be generated, simply updating the previousPosition
			exposureOn_ = false;
			previousPosition_ = operationCoordinate;
#ifdef ROGERBER_DEBUG
			std::cout << fmt::format("[Executor][Operation][Move]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
#endif
			break;
		case GerberOperationType::Flash:
#ifdef ROGERBER_DEBUG
			std::cout << fmt::format("[Executor][Operation][Flash]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
#endif
			break;
		default:
			throw GerberException("Unknown operation type");
	}
}

void GerberExecutor::Execute()
{
	for (auto it = gerber_.GetCommands().begin(); it != gerber_.GetCommands().end(); ++it) {
		auto cmd = (*it);

		switch(cmd->GetType())
		{
			case GerberCommandType::Format:
				{
					FormatStatement* format = static_cast<FormatStatement*>(cmd);
					setXCoordinateFormat(format->GetXIntegerPositions(), format->GetXDecimalPositions());
					setYCoordinateFormat(format->GetYIntegerPositions(), format->GetYDecimalPositions());

					coordinateSettings_.absoluteNotation_ = format->IsAbsoluteNotation();
					coordinateSettings_.leadingZeroOmission_ = format->IsLeadingZeroOmission();
				}
				break;
			case GerberCommandType::Unit:
				units_ = static_cast<UnitCommand*>(cmd)->GetUnits();
				break;
			case GerberCommandType::Interpolation:
				interpolationMode_ = static_cast<InterpolationMode*>(cmd)->GetMode();
				break;
			case GerberCommandType::Quadrant:
				quadrantMode_ = static_cast<QuadrantMode*>(cmd)->GetMode();
				break;
			case GerberCommandType::AperatureSelection:
				currentAperture_ = static_cast<ApertureSelection*>(cmd)->GetAperture();
				break;
			case GerberCommandType::Operation:
				{
					OperationStatement* op = static_cast<OperationStatement *>(cmd);
					GerberCoordinate coord;

					coord.X = convertXCoordinate(op->GetRawX(), &previousPosition_.X);
					coord.Y = convertYCoordinate(op->GetRawY(), &previousPosition_.Y);

					if(insideRegion_)
					{
						processOperationInsideRegion(op, coord);
					}
					else
					{
						processOperation(op, coord);
					}
				}
				break;

			case GerberCommandType::Region:
				insideRegion_ =  static_cast<RegionStatement*>(cmd)->IsStart();
				break;
			case GerberCommandType::ApertureDefinition:
				{
					auto aperture =  static_cast<ApertureDefinition*>(cmd);
					registerAperture(aperture);
				}
				break;
			default:
				throw GerberExecutorUnexpectedCommandException();
		}
	}
}

void GerberExecutor::setXCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions)
{
	coordinateSettings_.xIntegerPositions_ = integerPositions;
	coordinateSettings_.xDecimalPositions_ = decimalPositions;
}

void GerberExecutor::setYCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions)
{
	coordinateSettings_.yIntegerPositions_ = integerPositions;
	coordinateSettings_.yDecimalPositions_ = decimalPositions;
}

double GerberExecutor::convertXCoordinate(const std::string& raw, double* previous)
{
	if(raw.empty())
	{
		return *previous;	//per 4.9.1, if ommited, return the previous point
	}

	return baseCoordinateConversion(raw, coordinateSettings_.xIntegerPositions_, coordinateSettings_.xIntegerPositions_, coordinateSettings_.absoluteNotation_, previous);
}

double GerberExecutor::convertICoordinate(const std::string& raw)
{
	if(raw.empty())
	{
		return 0.0;	//J coordinates are "optional" and default to 0 per section 4.9.1
	}

	return baseCoordinateConversion(raw, coordinateSettings_.xIntegerPositions_, coordinateSettings_.xIntegerPositions_,
									false,
									nullptr);
}

double GerberExecutor::convertYCoordinate(const std::string& raw, double* previous)
{
	if(raw.empty())
	{
		return *previous;	//per 4.9.1, if ommited, return the previous point
	}

	return baseCoordinateConversion(raw, coordinateSettings_.yIntegerPositions_, coordinateSettings_.yIntegerPositions_, coordinateSettings_.absoluteNotation_, previous);
}

double GerberExecutor::convertJCoordinate(const std::string& raw)
{
	if(raw.empty())
	{
		return 0.0;	//J coordinates are "optional" and default to 0 per section 4.9.1
	}

	return baseCoordinateConversion(raw, coordinateSettings_.yIntegerPositions_, coordinateSettings_.yIntegerPositions_,
									false,
									nullptr);
}

double GerberExecutor::baseCoordinateConversion(const std::string& raw,
												unsigned int integerPositions,
												unsigned int decimalPositions,
												bool absolute,
												double* previous)
{
	//leading zeros can be ommited, ensure we are at least big enough as the decimal positions defines
	std::string decimalPortion;
	std::string integerPortion;
	if(coordinateSettings_.leadingZeroOmission_ )
	{
		if(raw.length() < decimalPositions)
		{
			throw GerberException("Coordinate string was smaller than defined number of decimal positions (leading zero omission)");
		}

		int integerTotal = raw.length()-decimalPositions;
		decimalPortion = raw.substr(integerTotal, decimalPositions);
		integerPortion = raw.substr(0, integerTotal);
	}
	else
	{
		if(raw.length() < integerPositions)
		{
			throw GerberException("Coordinate string was smaller than defined number of integer positions (trailing zero omission)");
		}

		int decimalTotal = raw.length()-integerPositions;
		integerPortion = raw.substr(0, integerPositions);
		decimalPortion = raw.substr(integerPositions, decimalTotal);
	}

	double ret = std::stod(integerPortion);

	double decimal = std::stod(decimalPortion);
	decimal /= std::pow((double)10.0,(double)decimalPortion.length());	//now shift the decimal over to the correct position 2 => 0.2 , 312 => .312

	ret += decimal;

	if(!absolute && previous != nullptr)
	{
		//relative notation, we want to return the real absolute so
		ret += *previous;
	}

	return ret;
}