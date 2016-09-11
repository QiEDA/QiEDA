#ifndef __GRAPHIC_ARC_H
#define __GRAPHIC_ARC_H

#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
	
class QICORE_EXPORT GraphicArc : public GraphicItem {
protected:
	Point center_;
	float radius_;
    Color color_;
    float angle0_;
    float angle1_;
public:
	GraphicArc(Point& center, float radius, float angle0, float angle1, const Color& color) : GraphicItem() {
		center_ = center;
		radius_ = radius;
		color_ = color;
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


	void draw(struct NVGcontext* nvg) override;
};

}
}

#endif