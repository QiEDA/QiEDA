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


void GerberProcessor::EmitCircle(unsigned int aperture,
						GerberCoordinate& center,
						double diameter,
						double holeDiameter)
{
#ifdef ROGERBER_DEBUG
	std::cout << fmt::format("[Processor][Emit][Circle]aperature={0},center.x={1},center.y={2},diameter={3},holeDiameter={4}",
							 aperture, center.X, center.Y, diameter, holeDiameter) << std::endl;
#endif
}

void GerberProcessor::EmitRectangle(unsigned int aperture, GerberCoordinate &center, double xSize, double ySize){
#ifdef ROGERBER_DEBUG
	std::cout << fmt::format("[Processor][Emit][Rectangle]aperature={0},center.x={1},center.y={2},xSize={3},ySize={4}",
							 aperture, center.X, center.Y, xSize, ySize) << std::endl;
#endif
}

void GerberProcessor::EmitObround(unsigned int aperture, GerberCoordinate &center, double xSize, double ySize,double holeDiameter){
#ifdef ROGERBER_DEBUG
	std::cout << fmt::format("[Processor][Emit][Obround]aperature={0},center.x={1},center.y={2},xSize={3},ySize={4},holeDiameter={5}",
							 aperture, center.X, center.Y, xSize, ySize, holeDiameter) << std::endl;
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

double GerberProcessor::getWidthFromAperture(ApertureDefinition* def)
{
	double width = 1.0f;
	if (def->GetPrimitive() == GerberAperturePrimitive::Circle) {
		auto circleAp = static_cast<CircleApertureDefinition *>(def);
		width = circleAp->GetDiameter();
		if (units_ == GerberUnitMode::Inches) {
			width *= 25.4;    //internally we treat everything as millimeters
		}
	}

	return width;
}

void GerberProcessor::processOperation(OperationStatement* op, GerberCoordinate& operationCoordinate)
{
	switch(op->GetOperationType())
	{
		case GerberOperationType::Interpolate: {
#ifdef ROGERBER_DEBUG
			std::cout << fmt::format("[Processor][Operation][Interpolate]coord.x={0},coord.y={1}",operationCoordinate.X, operationCoordinate.Y) << std::endl;
#endif
			exposureOn_ = true;

			if (!IS_APERTURE_LOADED()) {
				throw GerberException("No aperture loaded");
			}

			auto apertureProperties = getApertureDefinition(currentAperture_);

			if(apertureProperties == nullptr)
			{
				throw GerberException("Could not find aperture definition when trying to use it");
			}

			switch (interpolationMode_) {
				case GerberInterpolationMode::Linear: {
					double width = getWidthFromAperture(apertureProperties);
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

					double width = getWidthFromAperture(apertureProperties);

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
		case GerberOperationType::Flash: {
#ifdef ROGERBER_DEBUG
			std::cout << fmt::format("[Processor][Operation][Flash]coord.x={0},coord.y={1}", operationCoordinate.X,
									 operationCoordinate.Y) << std::endl;
#endif

			auto apertureProperties = getApertureDefinition(currentAperture_);
			if (apertureProperties == nullptr) {
				throw GerberException("Could not find aperture definition when trying to use it");
			}

			switch (apertureProperties->GetPrimitive()) {
				case GerberAperturePrimitive::Circle: {
					auto circleAp = static_cast<CircleApertureDefinition *>(apertureProperties);

					double diameter = circleAp->GetDiameter();
					if (units_ == GerberUnitMode::Inches) {
						diameter *= 25.4;    //internally we treat everything as millimeters
					}

					double holeDiameter = circleAp->GetHoleDiameter();
					if (units_ == GerberUnitMode::Inches) {
						holeDiameter *= 25.4;    //internally we treat everything as millimeters
					}

					EmitCircle(currentAperture_, operationCoordinate, diameter, holeDiameter);
				}
				break;
				case GerberAperturePrimitive::Rectangle: {
					auto rectAp = static_cast<RectangleApertureDefinition *>(apertureProperties);

					auto xSize = rectAp->GetXSize();
					auto ySize = rectAp->GetYSize();
					if (units_ == GerberUnitMode::Inches) {
						xSize *= 25.4;    //internally we treat everything as millimeters
						ySize *= 25.4;    //internally we treat everything as millimeters
					}

					EmitRectangle(currentAperture_, operationCoordinate, xSize, ySize);
				}
				break;
				case GerberAperturePrimitive::Obround: {
					auto rectAp = static_cast<ObroundApertureDefinition *>(apertureProperties);

					auto xSize = rectAp->GetXSize();
					auto ySize = rectAp->GetYSize();;
					auto holeDiam = rectAp->GetHoleDiameter();
					if (units_ == GerberUnitMode::Inches) {
						xSize *= 25.4;    //internally we treat everything as millimeters
						ySize *= 25.4;    //internally we treat everything as millimeters
						holeDiam *= 25.4;    //internally we treat everything as millimeters
					}

					EmitObround(currentAperture_, operationCoordinate, xSize, ySize, holeDiam);
				}
					break;
			}
			previousPosition_ = operationCoordinate;
		}
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
