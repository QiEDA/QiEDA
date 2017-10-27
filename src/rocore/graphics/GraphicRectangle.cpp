
#include <GL/glew.h>
#include "rocore/graphics/GraphicRectangle.hpp"

using namespace rocore::graphics;

BoundingBox GraphicRectangle::GetBoundingBox()
{
    return BoundingBox(start_,width_,height_);
}