#ifndef __SHAPE_H
#define __SHAPE_H

#include "qicore/qicore.hpp"

namespace qicore {
namespace geometry {
	
struct Point {
	float x;
	float y;
};
	
enum ShapeType {
	Line,
	Circle,
	Rectangle
};

class QICORE_EXPORT Shape {
protected:
	ShapeType type_;
public:
	Shape( ShapeType type ) {
		type_ = type;
	}

	virtual ~Shape() {}

	ShapeType GetType() {
		return type_;
	}
};

}
}

#endif