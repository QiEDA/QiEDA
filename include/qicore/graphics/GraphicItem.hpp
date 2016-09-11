#ifndef __GRAPHIC_ITEM_HPP
#define __GRAPHIC_ITEM_HPP

#include "qicore/qicore.hpp"

struct NVGcontext;

namespace qicore {
namespace graphics {

struct QICORE_EXPORT Point {
	float x;
	float y;

	Point(float a, float b)
	{
		x = a;
		y = b;
	}

	Point()
	{

	}

	Point operator-( const Point& p ) const
	{
		return Point(x - p.x, y-p.y);
	}

	Point operator-( const float& s ) const
	{
		return Point(x - s, y-s);
	}

	Point operator*( const float& s ) const
	{
		return Point(x * s, y*s);
	}
};

class QICORE_EXPORT BoundingBox {
private:
	Point origin;
	float width;
	float height;
public:
	BoundingBox(const Point& o, float w, float h)
	{
		origin = o;
		width = w;
		height = h;
	}

	Point Center() const
	{
		return Point(origin.x + width/2, origin.y + height/2);
	}

	float Left() const
	{
		return origin.x;
	}

	float Right() const
	{
		return origin.x + width;
	}

	float Top() const
	{
		return origin.y;
	}

	float Bottom() const
	{
		return origin.y + height;
	}

	bool Contains(const Point& p)
	{
		if(Left() <= p.x &&
				p.x <= Right() &&
				Top() <= p.y &&
				p.y <= Bottom())
		{
			return true;
		}
		return false;
	}
};

class QICORE_EXPORT GraphicItem {
public:
	GraphicItem() {
	}

	virtual ~GraphicItem() {}

	virtual void draw(struct NVGcontext* nvg)  = 0;

	virtual BoundingBox GetBoundingBox() = 0;
};

}
}

#endif