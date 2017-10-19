#include "rocore/graphics/GraphicRawLine.hpp"

using namespace rocore::graphics;

void GraphicRawLine::Draw(GraphicLayer* layer)
{
    layer->AddOperation(GraphicPaintOperationRawLine, 2, width_);
    layer->AddVertex(start_.x,start_.y);
    layer->AddVertex(end_.x, end_.y);
}

BoundingBox GraphicRawLine::GetBoundingBox()
{
	return BoundingBox(start_,0,0);
}