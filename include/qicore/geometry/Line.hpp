#ifndef __LINE_H
#define __LINE_H

#include "qicore/geometry/Shape.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace geometry {
	
class QICORE_EXPORT Line : public Shape {
protected:
	Point start_;
	Point end_;
	int width_;
public:
	Line(Point& start, Point& end, int width) : Shape( ShapeType::Line ) {
		start_ = start;
		end_ = end;
		width_ = width;
	}
}

}
}

#endif