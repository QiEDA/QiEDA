#include "rocore/graphics/GraphicGrid.hpp"
#include "rocore/Units.hpp"

using namespace rocore::graphics;


void GraphicGrid::Draw(GraphicPainter* painter) {
	painter->DrawCartesianGrid(-Units::MetersToInternalUnits(1),
					  Units::MetersToInternalUnits(1),
					  -Units::MetersToInternalUnits(1),
					  Units::MetersToInternalUnits(1),
					  Units::InchesToInternalUnits(0.01),
					  Units::InchesToInternalUnits(0.01));
}