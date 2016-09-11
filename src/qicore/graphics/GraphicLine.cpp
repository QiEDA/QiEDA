#include "qicore/graphics/GraphicLine.hpp"
#include "nanovg.h"

using namespace qicore::graphics;

void GraphicLine::draw(struct NVGcontext* nvg)
{
    nvgBeginPath(nvg);
    nvgMoveTo(nvg, start_.x, start_.y);
    nvgLineTo(nvg, end_.x, end_.y);
    nvgStrokeWidth(nvg, width_);
    nvgStrokeColor(nvg, nvgRGBA(color_.red(),color_.blue(),color_.blue(),color_.alpha()));
    nvgStroke(nvg);
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}