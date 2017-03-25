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

protected:
	const Gerber &gerber_;

	//graphic state
	GerberUnitMode units_;
	GerberInterpolationMode interpolationMode_;
	GerberQuadrantMode quadrantMode_;
	GerberCoordinateTranslator coordinateTranslator_;
};

class GerberExecutorUnexpectedCommandException : public GerberException {
public:
	GerberExecutorUnexpectedCommandException() : GerberException("Unknown execution command type") {}
};

}

#endif //ROEDA_GERBEREXECUTOR_HPP
