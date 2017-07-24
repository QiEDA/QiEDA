
#include <cmath>
#include "rogerber/CoordinateConverter.hpp"
#include "rogerber/GerberException.hpp"

using namespace rogerber;

void CoordinateConverter::SetXCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions)
{
	xIntegerPositions_ = integerPositions;
	xDecimalPositions_ = decimalPositions;
}

void CoordinateConverter::SetYCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions)
{
	yIntegerPositions_ = integerPositions;
	yDecimalPositions_ = decimalPositions;
}

double CoordinateConverter::baseCoordinateConversion(const std::string& raw,
												 unsigned int integerPositions,
												 unsigned int decimalPositions,
												 bool absolute,
												 double* previous)
{

	if(units_ == GerberUnitMode::Unknown)
	{
		throw GerberException("Unknown unit mode");
	}

	//leading zeros can be ommited, ensure we are at least big enough as the decimal positions defines
	std::string decimalPortion;
	std::string integerPortion;
	std::string coord = raw;
	unsigned int totalPositions = decimalPositions+integerPositions;
	if(leadingZeroOmission_ )
	{
		if(raw.length() < totalPositions)
		{
			coord.insert(coord.begin(), totalPositions - coord.length(), '0');
		}

	}
	else
	{
		if(raw.length() < totalPositions)
		{
			coord.append(totalPositions - coord.length(), '0');
		}
	}

	integerPortion = coord.substr(0, integerPositions);
	decimalPortion = coord.substr(integerPositions, decimalPositions);

	double ret = std::stod(integerPortion);

	double decimal = std::stod(decimalPortion);
	decimal /= std::pow((double)10.0,(double)decimalPortion.length());	//now shift the decimal over to the correct position 2 => 0.2 , 312 => .312

	ret += decimal;


	if(units_ == GerberUnitMode::Inches)
	{
		ret *= 25.4;	//internally we treat everything as millimeters
	}

	if(!absolute && previous != nullptr)
	{
		//relative notation, we want to return the real absolute so
		ret += *previous;
	}

	return ret;
}


double CoordinateConverter::ConvertXCoordinate(const std::string& raw, double* previous)
{
	if(raw.empty())
	{
		return *previous;	//per 4.9.1, if ommited, return the previous point
	}

	return baseCoordinateConversion(raw, xIntegerPositions_, xDecimalPositions_, absoluteNotation_, previous);
}

double CoordinateConverter::ConvertICoordinate(const std::string& raw)
{
	if(raw.empty())
	{
		return 0.0;	//J coordinates are "optional" and default to 0 per section 4.9.1
	}

	return baseCoordinateConversion(raw, xIntegerPositions_, xDecimalPositions_,
									false,
									nullptr);
}

double CoordinateConverter::ConvertYCoordinate(const std::string& raw, double* previous)
{
	if(raw.empty())
	{
		return *previous;	//per 4.9.1, if ommited, return the previous point
	}

	return baseCoordinateConversion(raw, yIntegerPositions_, yDecimalPositions_, absoluteNotation_, previous);
}

double CoordinateConverter::ConvertJCoordinate(const std::string& raw)
{
	if(raw.empty())
	{
		return 0.0;	//J coordinates are "optional" and default to 0 per section 4.9.1
	}

	return baseCoordinateConversion(raw, yIntegerPositions_, yDecimalPositions_,
									false,
									nullptr);
}