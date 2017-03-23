//
// Created by mroszko on 9/11/2016.
//

#ifndef ROEDA_UNITS_H
#define ROEDA_UNITS_H

namespace rocore {
class Units {
public:
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
};
}


#endif //ROEDA_UNITS_H
