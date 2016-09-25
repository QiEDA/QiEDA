#include "qicore/graphics/GraphicText.hpp"

using namespace qicore::graphics;

void GraphicText::Draw(GraphicLayer* layer)
{
}


BoundingBox GraphicText::GetBoundingBox()
{
    //todo cache bounds from nvgTextBounds in the draw func and return here

    return BoundingBox(start_,0,0);
}