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
	virtual void EmitLine(unsigned int aperture,
				  rogerber::GerberCoordinate& start,
				  rogerber::GerberCoordinate& stop,
				  int width) override;
	virtual void EmitArc(unsigned int aperture,
				 rogerber::GerberCoordinate& start,
				 rogerber::GerberCoordinate& stop,
				 rogerber::GerberCoordinate& center,
				 bool clockwise,
				 bool multiQuadrant,
				 int width) override;
};

#endif //ROEDA_GERBEROPENGLPROCESSOR_HPP
