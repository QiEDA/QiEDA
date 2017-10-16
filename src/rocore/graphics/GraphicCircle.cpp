#include "rocore/graphics/GraphicCircle.hpp"

using namespace rocore::graphics;

void GraphicCircle::Draw(GraphicLayer* layer)
{
    /*
     * Split into two triangles
     * *-------------*
     * | \           |
     * |   \         |
     * |     \       |
     * |       \     |
     * |         \   |
     * |           \ |
     * *-------------*
     */
    layer->AddOperation(GraphicPaintOperationCircle, 6, 1, radius_,0, center_.x, center_.y);
    layer->AddVertex(center_.x - radius_, center_.y + radius_); //upper left corner
    layer->AddVertex(center_.x - radius_, center_.y - radius_); //bottom left corner
    layer->AddVertex(center_.x + radius_, center_.y - radius_); //bottom right corner

    layer->AddVertex(center_.x + radius_, center_.y - radius_); //bottom right corner
    layer->AddVertex(center_.x + radius_, center_.y + radius_); //upper right corner
    layer->AddVertex(center_.x - radius_, center_.y + radius_); //upper left corner

}

BoundingBox GraphicCircle::GetBoundingBox()
{
    Point corner(radius_, radius_);

    return BoundingBox(center_-corner,radius_*2,radius_*2);
}