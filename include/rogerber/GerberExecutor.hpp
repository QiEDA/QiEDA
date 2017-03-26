//
// Created by mroszko on 3/24/2017.
//

#ifndef ROEDA_GERBEREXECUTOR_HPP
#define ROEDA_GERBEREXECUTOR_HPP

#include "rogerber/rogerber.hpp"
#include "rogerber/Gerber.hpp"
#include "rogerber/GerberCoordinateTranslator.hpp"
#include "rogerber/GerberException.hpp"

namespace rogerber {

class ROGERBER_EXPORT GerberExecutor {
public:
	GerberExecutor(const Gerber &gerber) : gerber_(gerber) {
	}

	const Gerber &GetGerber() const {
		return gerber_;
	}

	void Execute();
private:
	void processOperation(OperationStatement* op);
	void processOperationInsideRegion(OperationStatement* op);

protected:
	void EmitLine(unsigned int aperature,
				  GerberCoordinate& start,
				  GerberCoordinate& stop,
				  int width);
	void EmitArc(unsigned int aperature,
								 GerberCoordinate& start,
								 GerberCoordinate& stop,
								 GerberCoordinate& center,
								 bool clockwise,
								 bool multiQuadrant,
								 int width);

	const Gerber &gerber_;

	//graphic state
	GerberUnitMode units_;
	GerberInterpolationMode interpolationMode_;
	GerberQuadrantMode quadrantMode_;
	GerberCoordinateTranslator coordinateTranslator_;
	bool insideRegion_ = false;
	bool exposureOn_ = true;

	unsigned int currentAperature = 0;

	GerberCoordinate previousPos_;
};

class GerberExecutorUnexpectedCommandException : public GerberException {
public:
	GerberExecutorUnexpectedCommandException() : GerberException("Unknown execution command type") {}
};

}

#endif //ROEDA_GERBEREXECUTOR_HPP
