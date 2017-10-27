#ifndef __GRAPHIC_RAWLINE_H
#define __GRAPHIC_RAWLINE_H

#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicRawLine : public GraphicItem {
protected:
	Point start_;
	Point end_;
	double width_;
public:
	GraphicRawLine(Point& start, Point& end, double width) : GraphicItem() {
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
	BoundingBox GetBoundingBox() override;
};

}
}

#endif