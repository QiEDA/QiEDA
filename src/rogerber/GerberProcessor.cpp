//
// Created by mroszko on 3/24/2017.
//

#include <cmath>
#include <iostream>
#include <rogerber/GerberProcessor.hpp>
#include "rogerber/GerberProcessor.hpp"
#include "fmt/format.h"
#include "fmt/ostream.h"

using namespace rogerber;

#define ROGERBER_DEBUG

#define IS_APERTURE_LOADED() (currentAperture_ > 0)


void GerberProcessor::EmitLine(unsigned int aperture,
		                      GerberCoordinate& start,
							  GerberCoordinate& stop,
							   double width)
{
#ifdef ROGERBER_DEBUG
	std::cout << fmt::format("[Processor][Emit][Line]aperature={0},start.x={1},start.y={2},stop.x={3},stop.y={4},width={5}",
									aperture, start.X, start.Y, stop.X, stop.Y, width) << std::endl;
#endif

}

void GerberProcessor::EmitArc(unsigned int aperture,
							  GerberCoordinate& start,
							  GerberCoordinate& stop,
							  GerberCoordinate& center,
							  bool clockwise,
							  bool multiQuadrant,
							  double width)
{
#ifdef ROGERBER_DEBUG
	std::cout << fmt::format("[Processor][Emit][Arc]aperature={0},start.x={1},start.y={2},stop.x={3},stop.y={4},center.x={5},center.y",
							 aperture, start.X, start.Y, stop.X, stop.Y, center.X, center.Y) << std::endl;
#endif
}

void GerberProcessor::processOperationInsideRegion(OperationStatement* op, GerberCoordinate& xyCoordinate)
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

ApertureDefinition* GerberProcessor::getApertureDefinition(unsigned int aperture)
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

void GerberProcessor::registerAperture(ApertureDefinition* def)
{
	currentApertures_[def->GetNumber()] = def;
}

void GerberProcessor::processOperation(OperationStatement* op, GerberCoordinate& operationCoordinate)
{
	switch(op->GetOperationType())
	{
		case GerberOperationType::Interpolate:
			{
#ifdef ROGERBER_DEBUG
				std::cout << fmt::format("[Processor][Operation][Interpolate]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
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
					case GerberInterpolationMode::Linear: {
							double width = 1.0f;
							if (properties->GetPrimitive() == GerberAperturePrimitive::Circle) {
								auto circleAp = static_cast<CircleApertureDefinition *>(properties);
								width = circleAp->GetDiameter();
								if (units_ == GerberUnitMode::Inches) {
									width *= 25.4;    //internally we treat everything as millimeters
								}
							}
							EmitLine(currentAperture_, previousPosition_, operationCoordinate, width);
						}
						break;
					case GerberInterpolationMode::ArcClockwise:
					case GerberInterpolationMode::ArcCounterClockwise: {
							GerberCoordinate center;
							center.X = coordinateConverter_.ConvertICoordinate(op->GetRawI());
							center.Y = coordinateConverter_.ConvertJCoordinate(op->GetRawJ());
							//now since the I and J are relative, add the X and Y to it
							center.X += operationCoordinate.X;
							center.Y += operationCoordinate.Y;

							double width = 1.0f;
							if(properties->GetPrimitive() == GerberAperturePrimitive::Circle) {
								auto circleAp = static_cast<CircleApertureDefinition*>(properties);
								width = circleAp->GetDiameter();
								if(units_ == GerberUnitMode::Inches) {
									width *= 25.4;	//internally we treat everything as millimeters
								}
							}

							EmitArc(currentAperture_, previousPosition_, operationCoordinate,
									center, (interpolationMode_ == GerberInterpolationMode::ArcClockwise),
									quadrantMode_ == GerberQuadrantMode::Multi, width);
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
			std::cout << fmt::format("[Processor][Operation][Move]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
#endif
			break;
		case GerberOperationType::Flash:
#ifdef ROGERBER_DEBUG
			std::cout << fmt::format("[Processor][Operation][Flash]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
#endif
			break;
		default:
			throw GerberException("Unknown operation type");
	}
}

void GerberProcessor::Execute()
{
	for (auto it = gerber_.GetCommands().begin(); it != gerber_.GetCommands().end(); ++it) {
		auto cmd = (*it);

		switch(cmd->GetType())
		{
			case GerberCommandType::Format:
				{
					FormatStatement* format = static_cast<FormatStatement*>(cmd);
					coordinateConverter_.SetXCoordinateFormat(format->GetXIntegerPositions(), format->GetXDecimalPositions());
					coordinateConverter_.SetYCoordinateFormat(format->GetYIntegerPositions(), format->GetYDecimalPositions());

					coordinateConverter_.SetAbsoluteNotation(format->IsAbsoluteNotation());
					coordinateConverter_.SetLeadingZeroOmission(format->IsLeadingZeroOmission());
				}
				break;
			case GerberCommandType::Unit:
				{
					auto units = static_cast<UnitCommand *>(cmd)->GetUnits();
					units_ = units;
					coordinateConverter_.SetUnits(units);
				}
				break;
			case GerberCommandType::Interpolation:
				interpolationMode_ = static_cast<InterpolationMode*>(cmd)->GetMode();
				break;
			case GerberCommandType::Quadrant:
				quadrantMode_ = static_cast<QuadrantMode*>(cmd)->GetMode();
				break;
			case GerberCommandType::AperatureSelection:
				currentAperture_ = static_cast<ApertureSelection*>(cmd)->GetAperture();
#ifdef ROGERBER_DEBUG
				std::cout << fmt::format("[Processor][Aperature][Selection]aperature={0}",
										 currentAperture_ ) << std::endl;
#endif
				break;
			case GerberCommandType::Operation:
				{
					OperationStatement* op = static_cast<OperationStatement *>(cmd);
					GerberCoordinate coord;

					coord.X = coordinateConverter_.ConvertXCoordinate(op->GetRawX(), &previousPosition_.X);
					coord.Y = coordinateConverter_.ConvertYCoordinate(op->GetRawY(), &previousPosition_.Y);

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
#ifdef ROGERBER_DEBUG
				std::cout << fmt::format("[Processor][Aperature][Definition]aperature={0}",
										 aperture->GetNumber() ) << std::endl;
#endif
				}
				break;
			default:
				throw GerberExecutorUnexpectedCommandException();
		}
	}
}
