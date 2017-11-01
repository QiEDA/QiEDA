#ifndef __GRAPHIC_LINE_H
#define __GRAPHIC_LINE_H

#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"
#include <glm/glm.hpp>

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicLine : public GraphicItem {
protected:
	Point start_;
	Point end_;
	double width_;
	bool capped_;

	glm::highp_dvec2 getNormal() const;
public:
	GraphicLine(Point& start, Point& end, double width, bool capped = false) : GraphicItem() {
		start_ = start;
		end_ = end;
		width_ = width;
		capped_ = capped;
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

	void Draw(GraphicPainter* painter) override;

	BoundingBox GetBoundingBox() override;
};

}
}

#endif