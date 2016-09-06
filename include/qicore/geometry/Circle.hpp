#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "qicore/geometry/Shape.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace geometry {

class QICORE_EXPORT Circle {
protected:
	Point center_;
	double radius_;
public:
	Circle(Point& center, double radius) : Shape( ShapeType::Circle ) {
		center_ = center;
	}
	
	Point GetCenter() {
		return center_;
	}
	
	double GetRadius() {
		return radius_;
	}
}

}
}

#endif