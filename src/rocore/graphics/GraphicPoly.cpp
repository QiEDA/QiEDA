//
// Created by mroszko on 3/27/2017.
//

#include <cmath>
#include "rocore/graphics/GraphicPoly.hpp"

using namespace rocore::graphics;


BoundingBox GraphicPoly::GetBoundingBox() {
	double minX = DBL_MAX;
	double minY = DBL_MAX;
	double maxX = DBL_MIN;
	double maxY = DBL_MIN;
	for (auto it=points_.begin(); it != points_.end(); ++it)
	{
		minX = std::fmin(minX,(*it).x);
		minY = std::fmin(minY,(*it).y);

		maxX = std::fmax(maxX,(*it).x);
		maxY = std::fmax(maxY,(*it).y);
	}

	Point start;
	start.x = minX;
	start.y = minY;

	return BoundingBox(start,std::fabs(maxX-minY),std::fabs(maxY-minY));
}

void GraphicPoly::Draw(GraphicPainter* painter) {
	painter->DrawPolygon(points_);
}