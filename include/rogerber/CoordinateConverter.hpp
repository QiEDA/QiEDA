//
// Created by mroszko on 7/24/2017.
//

#ifndef ROEDA_COORDINATECONVERTER_HPP
#define ROEDA_COORDINATECONVERTER_HPP

#include <string>
#include "rogerber/rogerber.hpp"
#include "rogerber/GerberCommands.hpp"

namespace rogerber {

class ROGERBER_EXPORT CoordinateConverter {
public:
	void SetYCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions);
	void SetXCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions);

	double ConvertXCoordinate(const std::string& raw, double* previous);
	double ConvertYCoordinate(const std::string& raw, double* previous);
	double ConvertJCoordinate(const std::string& raw);

	/**
	 * Converts a given raw I coordinate to a number, this is on the X scale and length and always relative
	 * @param raw	Raw string
	 * @return
	 */
	double ConvertICoordinate(const std::string& raw);

	void SetUnits(GerberUnitMode units)
	{
		units_ = units;
	}

	void SetLeadingZeroOmission(bool hasLeadingZeroOmission)
	{
		leadingZeroOmission_ = hasLeadingZeroOmission;
	}

	void SetAbsoluteNotation(bool isAbsolute)
	{
		absoluteNotation_ = isAbsolute;
	}

private:

	double baseCoordinateConversion(const std::string& raw,
									unsigned int integerPositions,
									unsigned int decimalPositions,
									bool absolute,
									double* previous);

	GerberUnitMode units_;
	bool leadingZeroOmission_ = false;
	bool absoluteNotation_ = true;

	unsigned int xIntegerPositions_ = 0;
	unsigned int xDecimalPositions_ = 0;

	unsigned int yIntegerPositions_ = 0;
	unsigned int yDecimalPositions_ = 0;
};

}

#endif //ROEDA_COORDINATECONVERTER_HPP
