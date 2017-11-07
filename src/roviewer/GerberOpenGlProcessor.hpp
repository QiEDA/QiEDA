//
// Created by mroszko on 7/24/2017.
//

#ifndef ROEDA_GERBEROPENGLPROCESSOR_HPP
#define ROEDA_GERBEROPENGLPROCESSOR_HPP

#include "rogerber\GerberProcessor.hpp"
#include "rocore\graphics\GraphicLayer.hpp"

class GerberOpenGlProcessor : public rogerber::GerberProcessor {
public:
	GerberOpenGlProcessor(const rogerber::Gerber &gerber, rocore::graphics::GraphicLayer* layer)
			: GerberProcessor(gerber),
			  layer_(layer) {
	}
private:
	rocore::graphics::GraphicLayer* layer_;
protected:
	double getRadians(double degrees) {
		return (degrees * M_PI) / 180;
	}

	virtual void EmitLine(unsigned int aperture,
				  rogerber::GerberCoordinate& start,
				  rogerber::GerberCoordinate& stop,
						  double width) override;
	virtual void EmitArc(unsigned int aperture,
				 rogerber::GerberCoordinate& start,
				 rogerber::GerberCoordinate& stop,
				 rogerber::GerberCoordinate& center,
				 bool clockwise,
				 bool multiQuadrant,
						 double width) override;

	virtual void EmitCircle(unsigned int aperture,
							rogerber::GerberCoordinate& center,
										   double diameter,
										   double holeDiameter) override;

	virtual void EmitRectangle(unsigned int aperture,
							   rogerber::GerberCoordinate &center,
							   double length,
							   double width) override;

	virtual void EmitRegularPolygon(unsigned int aperture,
									rogerber::GerberCoordinate &center,
									double outerDiam, int
									numberOfVerts,
									float rotationAngle,
									double holeDiam) override;
};

#endif //ROEDA_GERBEROPENGLPROCESSOR_HPP
