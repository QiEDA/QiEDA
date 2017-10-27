#include "rocore/graphics/GraphicText.hpp"

using namespace rocore::graphics;

BoundingBox GraphicText::GetBoundingBox()
{
    //todo cache bounds from nvgTextBounds in the draw func and return here

    return BoundingBox(start_,0,0);
}