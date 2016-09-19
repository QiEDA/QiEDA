#ifndef __GRAPHIC_LINE_H
#define __GRAPHIC_LINE_H

#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
	
class QICORE_EXPORT GraphicLine : public GraphicItem {
protected:
	Point start_;
	Point end_;
	int width_;
public:
	GraphicLine(Point& start, Point& end, int width) : GraphicItem() {
		start_ = start;
		end_ = end;
		width_ = width;
	}

	const Point& GetStart()
	{
		return start_;
	}

	const Point& GetEnd()
	{
		return end_;
	}

	const int GetWidth()
	{
		return width_;
	}

	void Draw(GLPainter* painter, const Color& color) override;

	BoundingBox GetBoundingBox() override;
};

}
}

#endif