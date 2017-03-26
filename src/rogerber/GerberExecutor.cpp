//
// Created by mroszko on 3/24/2017.
//

#include "rogerber/GerberExecutor.hpp"

using namespace rogerber;


#define IS_APERATURE_LOADED() (currentAperature_ > 0)


void GerberExecutor::EmitLine(unsigned int aperature,
		                      GerberCoordinate& start,
							  GerberCoordinate& stop,
							  int width)
{

}

void GerberExecutor::EmitArc(unsigned int aperature,
							  GerberCoordinate& start,
							  GerberCoordinate& stop,
							  GerberCoordinate& center,
							  bool clockwise,
							  bool multiQuadrant,
							  int width)
{

}

void GerberExecutor::processOperationInsideRegion(OperationStatement* op)
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

void GerberExecutor::processOperation(OperationStatement* op)
{
	switch(op->GetOperationType())
	{
		case GerberOperationType::Interpolate:
			exposureOn_ = true;

			switch(interpolationMode_)
			{
				case GerberInterpolationMode::Linear:

					break;
				case GerberInterpolationMode::Clockwise:
				case GerberInterpolationMode::CounterClockwise:
					break;
			}

			break;
		case GerberOperationType::Move:
			break;
		case GerberOperationType::Flash:
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
					coordinateTranslator_.SetXFormat(format->GetXIntegerPositions(), format->GetXDecimalPositions());
					coordinateTranslator_.SetYFormat(format->GetYIntegerPositions(), format->GetYDecimalPositions());
					coordinateTranslator_.SetAbsoluteNotation(format->IsAbsoluteNotation());
					coordinateTranslator_.SetLeadingZeroOmission(format->IsLeadingZeroOmission());
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

				break;
			case GerberCommandType::Operation:
				{
					OperationStatement* op = static_cast<OperationStatement *>(cmd);
					if(insideRegion_)
					{
						processOperationInsideRegion(op);
					}
					else
					{
						processOperation(op);
					}
				}
				break;

			case GerberCommandType::Region:
				insideRegion_ =  static_cast<RegionStatement*>(cmd)->IsStart();
				break;
			default:
				throw GerberExecutorUnexpectedCommandException();
		}
	}
}