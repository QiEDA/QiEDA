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

	void Draw(GraphicLayer* layer) override;
	BoundingBox GetBoundingBox() override;
};

}
}

#endif