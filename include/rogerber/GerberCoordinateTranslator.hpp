//
// Created by mroszko on 3/24/2017.
//

#ifndef ROEDA_GERBERCOORDINATETRANSLATOR_HPP
#define ROEDA_GERBERCOORDINATETRANSLATOR_HPP

#include <string>
#include "rogerber/rogerber.hpp"

namespace rogerber {

struct ROGERBER_EXPORT GerberCoordinate {
	double X;
	double Y;
};

class ROGERBER_EXPORT GerberCoordinateTranslator {
public:
	GerberCoordinateTranslator() {
	}

	void SetXFormat(unsigned int integerPositions, unsigned int decimalPositions);

	void SetYFormat(unsigned int integerPositions, unsigned int decimalPositions);

	void SetLeadingZeroOmission(bool yes);

	void SetAbsoluteNotation(bool yes);

	double TranslateX(std::string rawX);

	double TranslateY(std::string rawY);

private:
	bool absoluteNotation_ = false;
	unsigned int xIntegerPositions_ = 0;
	unsigned int xDecimalPositions_ = 0;

	unsigned int yIntegerPositions_ = 0;
	unsigned int yDecimalPositions_ = 0;

	bool leadingZeroOmission_ = false;
	/*
	 * Previous translated coordinate, used for handling incremental notation
	 */
	GerberCoordinate previous_ = {0.0,0.0};

	double baseTranslation(std::string raw, unsigned int integerPositions, unsigned int decimalPositions, double& previous);
};

}

#endif //ROEDA_GERBERCOORDINATETRANSLATOR_HPP
