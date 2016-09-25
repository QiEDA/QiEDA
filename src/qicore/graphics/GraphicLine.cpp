#include "qicore/graphics/GraphicLine.hpp"

using namespace qicore::graphics;

void GraphicLine::Draw(GraphicLayer* layer)
{
    layer->AddOperation(GraphicPaintOperationLine, 2, width_);
    layer->AddVertex(start_.x,start_.y);
    layer->AddVertex(end_.x, end_.y);
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}