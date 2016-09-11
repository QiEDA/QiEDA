#include "qicore/graphics/GraphicCircle.hpp"
#include "nanovg.h"

using namespace qicore::graphics;

void GraphicCircle::draw(struct NVGcontext* nvg)
{
    nvgBeginPath(nvg);
    nvgCircle(nvg,center_.x,center_.y,radius_);
    nvgFillColor(nvg, nvgRGBA(color_.red(),color_.green(),color_.blue(),color_.alpha()));
    nvgFill(nvg);
}