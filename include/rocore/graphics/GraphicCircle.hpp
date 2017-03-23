#ifndef __GRAPHIC_CIRCLE_H
#define __GRAPHIC_CIRCLE_H

#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicCircle : public GraphicItem {
protected:
	Point center_;
	float radius_;
public:
    GraphicCircle(Point& center, float radius) : GraphicItem() {
		center_ = center;
		radius_ = radius;
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