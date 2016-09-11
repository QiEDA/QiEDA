#include "qicore/graphics/GraphicArc.hpp"
#include "nanovg.h"

using namespace qicore::graphics;

void GraphicArc::draw(struct NVGcontext* nvg)
{
    nvgBeginPath(nvg);
    nvgArc(nvg,center_.x,center_.y,radius_,angle0_, angle1_,NVG_CW);
    nvgStrokeWidth(nvg, 1);
    nvgStrokeColor(nvg, nvgRGBA(color_.red(),color_.blue(),color_.blue(),color_.alpha()));
    nvgStroke(nvg);
}