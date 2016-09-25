#include "qicore/graphics/GraphicLine.hpp"

using namespace qicore::graphics;

void GraphicLine::Draw(GraphicLayer* layer)
{
    layer->AddOperation(GraphicPaintOperationLine, 2);
    layer->AddVertex(start_.x,start_.y,0);
    layer->AddVertex(end_.x, end_.y, 0);
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}