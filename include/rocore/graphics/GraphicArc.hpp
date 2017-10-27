#ifndef __GRAPHIC_ARC_H
#define __GRAPHIC_ARC_H

#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicArc : public GraphicItem {
protected:
	Point center_;
	float radius_;
    float angleStart_;
    float angleEnd_;
public:
	GraphicArc(Point& center, float radius, float angleStart, float angleEnd) : GraphicItem() {
		center_ = center;
		radius_ = radius;
		angleStart_ = angleStart;
		angleEnd_ = angleEnd;
	}

	const Point& GetCenter()
	{
		return center_;
	}

	const float GetRadius()
	{
		return radius_;
	}

	BoundingBox GetBoundingBox() override;
};

}
}

#endif