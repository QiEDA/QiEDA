//
// Created by mroszko on 9/10/2016.
//

#ifndef QIEDA_COLOR_H
#define QIEDA_COLOR_H

#include "qicore/qicore.hpp"

struct NVGcontext;

namespace qicore {
namespace graphics {


class QICORE_EXPORT Color {
protected:
    int r_;
    int g_;
    int b_;
    int a_;
public:
    Color(int r, int g, int b, int a = 255);
    Color();

    int green() const
    {
        return g_;
    }

    int red() const
    {
        return r_;
    }

    int blue() const
    {
        return b_;
    }

    int alpha() const
    {
        return a_;
    }
};

namespace Colors {
    const Color Black(0,0,0);
    const Color White(255,255,255);
    const Color Silver(192,192,192);
    const Color Gray(128,128,128);
    const Color DimGray(105,105,105);

    const Color Maroon(128,0,0);
    const Color Crimson(220,20,60);
    const Color Red(255,0,0);
    const Color Magenta(255,0,255);
    const Color Purple(128,0,128);
    const Color Pink(255,192,203);
    const Color Fuschia(255,0,255);
    const Color LightPink(255,182,193);

    const Color LightGreen(144,238,144);
    const Color Green(0,128,0);
    const Color Lime(0,255,0);
    const Color GreenYellow(173,255,47);

    const Color Cyan(0,255,255);
    const Color DarkBlue(0,0,139);
    const Color Blue(0,0,255);
    const Color Navy(0,0,128);
    const Color LightBlue(173,216,230);

    const Color Yellow(255,255,0);
    const Color Orange(255,165,0);
    const Color OrangeRed(255,69,0);
}

}
}

#endif //QIEDA_COLOR_H
