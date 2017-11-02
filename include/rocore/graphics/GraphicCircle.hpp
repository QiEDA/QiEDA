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
	float holeRadius_;
	bool hasHole_;
public:
    GraphicCircle(Point& center, float radius) : GraphicItem() {
		center_ = center;
		radius_ = radius;
		hasHole_ = false;
	}

	GraphicCircle(Point& center, float radius, float holeRadius) : GraphicCircle(center, radius) {
		holeRadius_ = holeRadius;
		hasHole_ = true;
	}

	const Point& GetCenter()
	{
		return center_;
	}

	float GetRadius() const
	{
		return radius_;
	}

	float GetHoleRadius() const
	{
		return holeRadius_;
	}

	bool GetHasHole() const
	{
		return hasHole_;
	}

	void Draw(GraphicPainter* painter) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif