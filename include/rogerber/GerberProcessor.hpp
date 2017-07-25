//
// Created by mroszko on 3/24/2017.
//

#ifndef ROEDA_GERBEREXECUTOR_HPP
#define ROEDA_GERBEREXECUTOR_HPP

#include <map>
#include <memory>
#include "rogerber/rogerber.hpp"
#include "rogerber/Gerber.hpp"
#include "rogerber/GerberException.hpp"
#include "rogerber/CoordinateConverter.hpp"

namespace rogerber {

struct ROGERBER_EXPORT GerberCoordinate {
	double X;
	double Y;
};

struct AperatureProperties
{
	unsigned int Width;
};


class ROGERBER_EXPORT GerberProcessor {
public:
	GerberProcessor(const Gerber &gerber) : gerber_(gerber) {
	}

	const Gerber &GetGerber() const {
		return gerber_;
	}

	void Execute();
private:
	void processOperation(OperationStatement* op, GerberCoordinate& xyCoordinate);
	void processOperationInsideRegion(OperationStatement* op, GerberCoordinate& xyCoordinate);

	ApertureDefinition* getApertureDefinition(unsigned int aperature);
	void registerAperture(ApertureDefinition* def);
protected:
	virtual void EmitLine(unsigned int aperture,
				  GerberCoordinate& start,
				  GerberCoordinate& stop,
				  int width);
	virtual void EmitArc(unsigned int aperture,
								 GerberCoordinate& start,
								 GerberCoordinate& stop,
								 GerberCoordinate& center,
								 bool clockwise,
								 bool multiQuadrant,
								 int width);

	const Gerber &gerber_;

	CoordinateConverter coordinateConverter_;
	GerberInterpolationMode interpolationMode_;
	GerberQuadrantMode quadrantMode_;
	bool insideRegion_ = false;
	bool exposureOn_ = true;

	unsigned int currentAperture_ = 0;

	GerberCoordinate previousPosition_;

	std::map<unsigned int, ApertureDefinition *> currentApertures_;
};

class GerberExecutorUnexpectedCommandException : public GerberException {
public:
	GerberExecutorUnexpectedCommandException() : GerberException("Unknown execution command type") {}
};

}

#endif //ROEDA_GERBEREXECUTOR_HPP
