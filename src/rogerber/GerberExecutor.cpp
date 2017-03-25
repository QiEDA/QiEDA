//
// Created by mroszko on 3/24/2017.
//

#include "rogerber/GerberExecutor.hpp"

using namespace rogerber;

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
			default:
				throw GerberExecutorUnexpectedCommandException();
		}
	}
}