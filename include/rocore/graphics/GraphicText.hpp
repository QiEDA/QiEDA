#ifndef __GRAPHIC_TEXT_H
#define __GRAPHIC_TEXT_H

#include <string>
#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	
class ROCORE_EXPORT GraphicText : public GraphicItem {
protected:
	Point start_;
	float width_;
	float height_;
	std::string str_;
    float size_;
public:
	GraphicText(Point& start, const char* str, float size) : GraphicItem() {
		start_ = start;
		str_.assign(str);
        size_ = size;
	}

	const Point& GetOrigin()
	{
		return start_;
	}

	const float GetWidth()
	{
		return width_;
	}
	BoundingBox GetBoundingBox() override;
};

}
}

#endif