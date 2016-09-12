//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_UNITS_H
#define QIEDA_UNITS_H

namespace qicore {
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


#endif //QIEDA_UNITS_H
