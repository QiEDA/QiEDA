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
    float angle0_;
    float angle1_;
public:
	GraphicArc(Point& center, float radius, float angle0, float angle1) : GraphicItem() {
		center_ = center;
		radius_ = radius;
        angle0_ = angle0;
        angle1_ = angle1;
	}

	const Point& GetCenter()
	{
		return center_;
	}

	const float GetRadius()
	{
		return radius_;
	}


	void Draw(GraphicLayer* layer) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif