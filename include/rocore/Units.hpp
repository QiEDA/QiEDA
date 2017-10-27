//
// Created by mroszko on 9/11/2016.
//

#ifndef ROEDA_UNITS_H
#define ROEDA_UNITS_H


namespace rocore {
class Units {
public:
    enum class Type
    {
        Mils,
        Millimeters,
        Inches
    };

    static float MetersToInternalUnits(float m) {
        return m;
    }

    static float MillimetersToInternalUnits(float mm) {
        return mm/1000.0f;
    }

    static float InchesToInternalUnits(float in) {
        return in*0.0254f;
    }

    static float MilsToInternalUnits(float mils) {
        return mils*2.54e-5;
    }

    static double MilsToMillimeters(double mils) {
        return mils*0.0254;
    }

    static double MilsToInches(double mils) {
        return mils*0.001;
    }

    static double MillimetersToInches(double mils) {
        return mils*0.0393701;
    }

    static double MillimetersToMils(double mils) {
        return mils*39.3701;
    }
    static double InchesToMillimeters(double mils) {
        return mils*25.4;
    }

    static double InchesToMils(double mils) {
        return mils*1000;
    }

    static double Convert(double value, Units::Type original, Units::Type target) {
        switch(original) {
            case Units::Type::Mils:
                switch(target) {
                    case Units::Type::Mils:
                        return value;
                    case Units::Type::Inches:
                        return MilsToInches(value);
                    case Units::Type::Millimeters:
                        return MilsToMillimeters(value);
                }
            case Units::Type::Inches:
                switch(target) {
                    case Units::Type::Mils:
                        return InchesToMils(value);
                    case Units::Type::Inches:
                        return value;
                    case Units::Type::Millimeters:
                        return InchesToMillimeters(value);
                }
            case Units::Type::Millimeters:
                switch(target) {
                    case Units::Type::Mils:
                        return MillimetersToMils(value);
                    case Units::Type::Inches:
                        return MillimetersToInches(value);
                    case Units::Type::Millimeters:
                        return value;
                }
            default:
                break;
        }

        throw std::logic_error("encountered undefined unit conversions");
    }
};
}


#endif //ROEDA_UNITS_H
