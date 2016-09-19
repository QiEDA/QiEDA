#include "qicore/graphics/GraphicLine.hpp"

using namespace qicore::graphics;

void GraphicLine::Draw(GLPainter* painter, const Color& color)
{
    painter->DrawLine(start_, end_, width_, color);
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}