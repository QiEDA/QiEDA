#include "rogerber/CoordinateConverter.hpp"
#include "gtest/gtest.h"

using namespace rogerber;

TEST(CoordinateConverter, ConvertXCoordinateBasic) {
	CoordinateConverter conv;

	double previousX = 0;
	std::string sample = "100100";
	conv.SetXCoordinateFormat(3,3);

	EXPECT_DOUBLE_EQ(100.1, conv.ConvertXCoordinate(sample, &previousX));
}

TEST(CoordinateConverter, ConvertXCoordinateInchesConversion) {
	CoordinateConverter conv;

	double previousX = 0;
	std::string sample = "250000";
	conv.SetUnits(GerberUnitMode::Inches);
	conv.SetXCoordinateFormat(2,6);
	conv.SetLeadingZeroOmission(true);

	EXPECT_DOUBLE_EQ(6.35, conv.ConvertXCoordinate(sample, &previousX));
}