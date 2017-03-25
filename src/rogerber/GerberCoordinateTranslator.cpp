//
// Created by mroszko on 3/24/2017.
//

#include <cmath>
#include "rogerber/GerberCoordinateTranslator.hpp"
#include "rogerber/GerberException.hpp"

using namespace rogerber;


void GerberCoordinateTranslator::SetXFormat(unsigned int integerPositions, unsigned int decimalPositions)
{
	xIntegerPositions_ = integerPositions;
	xDecimalPositions_ = decimalPositions;
}

void GerberCoordinateTranslator::SetYFormat(unsigned int integerPositions, unsigned int decimalPositions)
{
	yIntegerPositions_ = integerPositions;
	yDecimalPositions_ = decimalPositions;
}

double GerberCoordinateTranslator::baseTranslation(std::string raw, unsigned int integerPositions, unsigned int decimalPositions)
{
	//leading zeros can be ommited, ensure we are at least big enough as the decimal positions defines
	std::string decimalPortion;
	std::string integerPortion;
	if(leadingZeroOmission_ )
	{
		if(raw.length() < decimalPositions)
		{
			throw GerberException("Coordinate string was smaller than defined number of decimal positions (leading zero omission)");
		}

		int integerTotal = raw.length()-decimalPositions;
		decimalPortion = raw.substr(integerTotal, decimalPositions);
		integerPortion = raw.substr(0, integerTotal);
	}

	if(!leadingZeroOmission_ )
	{
		if(raw.length() < integerPositions)
		{
			throw GerberException("Coordinate string was smaller than defined number of integer positions (trailing zero omission)");
		}

		int decimalTotal = raw.length()-integerPositions;
		integerPortion = raw.substr(0, integerPositions);
		decimalPortion = raw.substr(integerPositions, decimalTotal);
	}

	double ret = std::stod(integerPortion);

	double decimal = std::stod(decimalPortion);
	decimal /= std::pow((double)10.0,(double)decimalPortion.length());	//now shift the decimal over to the correct position 2 => 0.2 , 312 => .312

	ret += decimal;

	return ret;
}

double GerberCoordinateTranslator::TranslateX(std::string rawX)
{
	return baseTranslation(rawX, xIntegerPositions_, xDecimalPositions_);
}

double GerberCoordinateTranslator::TranslateY(std::string rawY)
{
	return baseTranslation(rawY, yIntegerPositions_, yDecimalPositions_);
}

void GerberCoordinateTranslator::SetLeadingZeroOmission(bool yes)
{
	leadingZeroOmission_ = yes;
}

void GerberCoordinateTranslator::SetAbsoluteNotation(bool yes)
{
	absoluteNotation_ = yes;
}