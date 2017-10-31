#include "rocore/graphics/GraphicArc.hpp"
#include "rocore/Units.hpp"

using namespace rocore::graphics;

BoundingBox GraphicArc::GetBoundingBox()
{
    Point corner(radius_, radius_);

    return BoundingBox(center_-corner,radius_*2,radius_*2);
}


void GraphicArc::Draw(GraphicPainter* painter)
{
    painter->DrawArc(center_, radius_, angleStart_, angleEnd_, Units::MilsToInternalUnits(10), filled_);
}