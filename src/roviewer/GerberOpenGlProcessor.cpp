
#include "GerberOpenGlProcessor.hpp"
#include "rocore/Units.hpp"
#include "rocore/graphics/GraphicLine.hpp"
#include "rocore/graphics/GraphicArc.hpp"
#include "rocore/graphics/GraphicCircle.hpp"
#include "rocore/graphics/GraphicRectangle.hpp"

void GerberOpenGlProcessor::EmitArc(unsigned int aperture, rogerber::GerberCoordinate &start,
									rogerber::GerberCoordinate &stop, rogerber::GerberCoordinate &center,
									bool clockwise, bool multiQuadrant, double width) {

	//the two radii are supposed to be equal
	//however the gerber spec talks about deviation...because the format stores start and stop endpoints instead of angles
	//and precision errors could occur when saving
	//our workaround is compute both radii and take the average for now
	double startCenterRadius = sqrt(pow(center.X - start.X, 2) + pow(center.Y - start.Y,2));
	double stopCenterRadius = sqrt(pow(center.X - stop.X, 2) + pow(center.Y - stop.Y,2));

	double radius = (startCenterRadius + stopCenterRadius) / 2;

	//start angle calc
	double startAngle = std::atan2(center.Y - start.Y, center.X - start.X);

	//stop angle calc
	double stopAngle = std::atan2(center.Y - stop.Y, center.X - stop.X);

	rocore::graphics::Point p1;
	p1.x = rocore::Units::MillimetersToInternalUnits(center.X);
	p1.y = rocore::Units::MillimetersToInternalUnits(center.Y);

	auto gral = new rocore::graphics::GraphicArc(p1, rocore::Units::MillimetersToInternalUnits(radius), startAngle, stopAngle, rocore::Units::MillimetersToInternalUnits(width));
	layer_->AddItem(gral);
}

void GerberOpenGlProcessor::EmitLine(unsigned int aperture, rogerber::GerberCoordinate &start,
									 rogerber::GerberCoordinate &stop, double width) {

	rocore::graphics::Point p1;
	p1.x = rocore::Units::MillimetersToInternalUnits(start.X);
	p1.y = rocore::Units::MillimetersToInternalUnits(start.Y);

	rocore::graphics::Point p2;
	p2.x = rocore::Units::MillimetersToInternalUnits(stop.X);
	p2.y = rocore::Units::MillimetersToInternalUnits(stop.Y);

	auto gral = new rocore::graphics::GraphicLine(p1,p2, rocore::Units::MillimetersToInternalUnits(width), true);

	layer_->AddItem(gral);
}

void GerberOpenGlProcessor::EmitCircle(unsigned int aperture,
									   rogerber::GerberCoordinate& center,
								 double diameter,
								 double holeDiameter)
{
	rocore::graphics::Point p1;
	p1.x = rocore::Units::MillimetersToInternalUnits(center.X);
	p1.y = rocore::Units::MillimetersToInternalUnits(center.Y);

	rocore::graphics::GraphicCircle* circle;
	if(holeDiameter != 0.0) {
		circle = new rocore::graphics::GraphicCircle(p1, rocore::Units::MillimetersToInternalUnits(diameter/2), rocore::Units::MillimetersToInternalUnits(holeDiameter/2) );
	}
	circle = new rocore::graphics::GraphicCircle(p1, rocore::Units::MillimetersToInternalUnits(diameter/2));

	layer_->AddItem(circle);
}

void GerberOpenGlProcessor::EmitRectangle(unsigned int aperture,
												  rogerber::GerberCoordinate &center,
						   double xSize,
						   double ySize) {

	rocore::graphics::Point p1;
	p1.x = rocore::Units::MillimetersToInternalUnits(center.X - xSize/2);
	p1.y = rocore::Units::MillimetersToInternalUnits(center.Y - ySize/2);

	auto rect = new rocore::graphics::GraphicRectangle(p1, rocore::Units::MillimetersToInternalUnits(xSize), rocore::Units::MillimetersToInternalUnits(ySize));

	layer_->AddItem(rect);
}