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
    const Color Red(255,0,0);
    const Color Green(0,255,0);
    const Color Blue(0,0,255);
    const Color Yellow(255,255,0);
}

}
}

#endif //QIEDA_COLOR_H
