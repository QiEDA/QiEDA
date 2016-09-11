#include "qicore/graphics/GraphicText.hpp"
#include "nanovg.h"

using namespace qicore::graphics;

void GraphicText::draw(struct NVGcontext* nvg)
{
    nvgBeginPath(nvg);
    nvgFontSize(nvg, size_);
    nvgFontFace(nvg, "sans");
    nvgTextAlign(nvg, NVG_ALIGN_LEFT|NVG_ALIGN_BOTTOM);
    nvgText(nvg,start_.x,start_.y, str_.c_str(), NULL);
    nvgFillColor(nvg, nvgRGBA(color_.red(),color_.green(),color_.blue(),color_.alpha()));
    nvgFill(nvg);
}


BoundingBox GraphicText::GetBoundingBox()
{
    //todo cache bounds from nvgTextBounds in the draw func and return here

    return BoundingBox(start_,0,0);
}