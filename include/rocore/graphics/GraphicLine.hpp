#ifndef __GRAPHIC_LINE_H
#define __GRAPHIC_LINE_H

#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicLine : public GraphicItem {
protected:
	Point start_;
	Point end_;
	double width_;
public:
	GraphicLine(Point& start, Point& end, double width) : GraphicItem() {
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

	void Draw(GraphicLayer* layer) override;

	BoundingBox GetBoundingBox() override;
};

}
}

#endif