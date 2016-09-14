#include "qicore/graphics/GraphicLine.hpp"

using namespace qicore::graphics;

void GraphicLine::draw(GLPainter* painter)
{
    painter->DrawLine(start_, end_, width_, color_);
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}