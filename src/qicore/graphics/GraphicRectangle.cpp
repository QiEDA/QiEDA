#include "qicore/graphics/GraphicRectangle.hpp"
#include "nanovg.h"

using namespace qicore::graphics;

void GraphicRectangle::draw(struct NVGcontext* nvg)
{
    nvgBeginPath(nvg);
    nvgRect(nvg,start_.x,start_.y,width_,height_);
    nvgFillColor(nvg, nvgRGBA(color_.red(),color_.green(),color_.blue(),color_.alpha()));
    nvgFill(nvg);
}