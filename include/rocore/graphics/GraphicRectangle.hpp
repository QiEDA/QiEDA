#ifndef __GRAPHIC_RECTANGLE_H
#define __GRAPHIC_RECTANGLE_H

#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicRectangle : public GraphicItem {
protected:
	Point start_;
	float width_;
	float height_;
    Color color_;
public:
	GraphicRectangle(Point& start, float width, float height) : GraphicItem() {
		start_ = start;
		width_ = width;
		height_ = height;
	}

	const Point& GetOrigin()
	{
		return start_;
	}

	const float GetWidth()
	{
		return width_;
	}

	const float GetHeight()
	{
		return height_;
	}

	void Draw(GraphicPainter* painter) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif