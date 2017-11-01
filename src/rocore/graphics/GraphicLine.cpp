#include "rocore/graphics/GraphicLine.hpp"

using namespace rocore::graphics;


void GraphicLine::Draw(GraphicPainter* painter) {
	painter->DrawLine(start_, end_, width_);

	if(capped_) {
		painter->DrawCircle(start_, width_/2, true);
		painter->DrawCircle(end_, width_/2, true);
	}
}

glm::highp_dvec2 GraphicLine::getNormal() const {
    double dx = end_.x - start_.x;
    double dy = end_.y - start_.y;

    return glm::normalize(glm::highp_dvec2(-dy, dx));
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}