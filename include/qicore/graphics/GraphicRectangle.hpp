#ifndef __GRAPHIC_RECTANGLE_H
#define __GRAPHIC_RECTANGLE_H

#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
	
class QICORE_EXPORT GraphicRectangle : public GraphicItem {
protected:
	Point start_;
	float width_;
	float height_;
    Color color_;
public:
	GraphicRectangle(Point& start, float width, float height, const Color& color) : GraphicItem() {
		start_ = start;
		width_ = width;
		height_ = height;
        color_ = color;
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

	void draw(GLPainter* painter) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif