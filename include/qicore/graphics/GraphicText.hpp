#ifndef __GRAPHIC_TEXT_H
#define __GRAPHIC_TEXT_H

#include <string>
#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
	
class QICORE_EXPORT GraphicText : public GraphicItem {
protected:
	Point start_;
	float width_;
	float height_;
    Color color_;
	std::string str_;
    float size_;
public:
	GraphicText(Point& start, const char* str, float size, const Color& color) : GraphicItem() {
		start_ = start;
		str_.assign(str);
        color_ = color;
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

	void draw(struct NVGcontext* nvg) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif