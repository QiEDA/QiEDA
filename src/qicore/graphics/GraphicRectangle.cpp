
#include <GL/glew.h>
#include "qicore/graphics/GraphicRectangle.hpp"

using namespace qicore::graphics;

void GraphicRectangle::Draw(GraphicLayer* layer)
{
    layer->AddOperation(GraphicPaintOperationQuad, 4);
    layer->AddVertex(start_.x,start_.y,0);
    layer->AddVertex(start_.x+width_, start_.y, 0);
    layer->AddVertex(start_.x+width_, start_.y+height_,0);
    layer->AddVertex(start_.x, start_.y+height_,0);
}


BoundingBox GraphicRectangle::GetBoundingBox()
{
    return BoundingBox(start_,width_,height_);
}