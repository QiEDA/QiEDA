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
	double radius_;
	double angleStart_;
	double angleEnd_;
	bool filled_;
	double thickness_;
public:
	GraphicArc(Point& center, double radius, double angle0, double angle1, double thickness) : GraphicArc(center, radius, angle0, angle1) {
		thickness_ = thickness;
		filled_ = false;
	}
	GraphicArc(Point& center, double radius, double angle0, double angle1) : GraphicItem() {
		center_ = center;
		radius_ = radius;
		filled_ = true;
		if(angle0 < angle1) {
			angleStart_ = angle0;
			angleEnd_ = angle1;
		} else {
			angleStart_ = angle1;
			angleEnd_ = angle0;
		}
	}

	const Point& GetCenter()
	{
		return center_;
	}

	const double GetRadius()
	{
		return radius_;
	}

	void Draw(GraphicPainter* painter) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif