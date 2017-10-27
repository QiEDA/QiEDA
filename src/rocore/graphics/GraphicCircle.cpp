#include "rocore/graphics/GraphicCircle.hpp"

using namespace rocore::graphics;


void GraphicCircle::Draw(GraphicPainter* painter)
{
    painter->DrawCircle(center_, radius_);
}

BoundingBox GraphicCircle::GetBoundingBox()
{
    Point corner(radius_, radius_);

    return BoundingBox(center_-corner,radius_*2,radius_*2);
}