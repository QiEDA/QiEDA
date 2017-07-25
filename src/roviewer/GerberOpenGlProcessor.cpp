
#include "GerberOpenGlProcessor.hpp"
#include "rocore/Units.hpp"
#include "rocore/graphics/GraphicLine.hpp"

void GerberOpenGlProcessor::EmitArc(unsigned int aperture, rogerber::GerberCoordinate &start,
									rogerber::GerberCoordinate &stop, rogerber::GerberCoordinate &center,
									bool clockwise, bool multiQuadrant, int width) {

}

void GerberOpenGlProcessor::EmitLine(unsigned int aperture, rogerber::GerberCoordinate &start,
									 rogerber::GerberCoordinate &stop, int width) {

	rocore::graphics::Point p1;
	p1.x = rocore::Units::MillimetersToInternalUnits(start.X);
	p1.y = rocore::Units::MillimetersToInternalUnits(start.Y);

	rocore::graphics::Point p2;
	p2.x = rocore::Units::MillimetersToInternalUnits(stop.X);
	p2.y = rocore::Units::MillimetersToInternalUnits(stop.Y);

	rocore::graphics::GraphicLine* gral = new rocore::graphics::GraphicLine(p1,p2, width);

	layer_->AddItem(gral);
}