#include "rocore/graphics/GraphicArc.hpp"

using namespace rocore::graphics;

BoundingBox GraphicArc::GetBoundingBox()
{
    Point corner(radius_, radius_);

    return BoundingBox(center_-corner,radius_*2,radius_*2);
}