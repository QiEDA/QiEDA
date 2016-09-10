#include "qicore/graphics/Color.hpp"
#include "nanovg.h"

using namespace qicore::graphics;

Color::Color(int r, int g, int b, int a) {
    r_ = r;
    g_ = g;
    b_ = b;
    a_ = a;
}

Color::Color() {
    r_ = 255;
    g_ = 255;
    b_ = 255;
    a_ = 255;
}