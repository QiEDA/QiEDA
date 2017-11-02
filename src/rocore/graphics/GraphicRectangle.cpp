
#include <GL/glew.h>
#include "rocore/graphics/GraphicRectangle.hpp"

using namespace rocore::graphics;

BoundingBox GraphicRectangle::GetBoundingBox()
{
    return BoundingBox(start_,width_,height_);
}


void GraphicRectangle::Draw(GraphicPainter* painter) {
    painter->DrawRectangle(this->start_, width_, height_);
}