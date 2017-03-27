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
	double baseCoordinateConversion(const std::string& raw,
									unsigned int integerPositions,
									unsigned int decimalPositions,
									bool absolute,
									double* previous);
	void setYCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions);
	void setXCoordinateFormat(unsigned int integerPositions, unsigned int decimalPositions);
	double convertXCoordinate(const std::string& raw, double* previous);
	double convertYCoordinate(const std::string& raw, double* previous);
	double convertJCoordinate(const std::string& raw);

	/**
	 * Converts a given raw I coordinate to a number, this is on the X scale and length and always relative
	 * @param raw	Raw string
	 * @return
	 */
	double convertICoordinate(const std::string& raw);

	ApertureDefinition* getApertureDefinition(unsigned int aperature);
	void registerAperture(ApertureDefinition* def);
protected:
	void EmitLine(unsigned int aperture,
				  GerberCoordinate& start,
				  GerberCoordinate& stop,
				  int width);
	void EmitArc(unsigned int aperture,
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
	bool insideRegion_ = false;
	bool exposureOn_ = true;

	unsigned int currentAperture_ = 0;

	GerberCoordinate previousPosition_;
	struct {
		bool leadingZeroOmission_ = false;
		bool absoluteNotation_ = true;

		unsigned int xIntegerPositions_ = 0;
		unsigned int xDecimalPositions_ = 0;

		unsigned int yIntegerPositions_ = 0;
		unsigned int yDecimalPositions_ = 0;
	} coordinateSettings_;

	std::map<unsigned int, ApertureDefinition *> currentApertures_;
};

class GerberExecutorUnexpectedCommandException : public GerberException {
public:
	GerberExecutorUnexpectedCommandException() : GerberException("Unknown execution command type") {}
};

}

#endif //ROEDA_GERBEREXECUTOR_HPP
