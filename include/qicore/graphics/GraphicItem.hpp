#ifndef __GRAPHIC_ITEM_HPP
#define __GRAPHIC_ITEM_HPP

#include "qicore/qicore.hpp"
#include "qicore/graphics/GLPainter.hpp"
#include "qicore/graphics/BoundingBox.hpp"


namespace qicore {
namespace graphics {

class GLPainter;

class QICORE_EXPORT GraphicItem {
public:
	GraphicItem() {
	}

	virtual ~GraphicItem() {}

	virtual void draw(GLPainter* painter)  = 0;

	virtual BoundingBox GetBoundingBox() = 0;
};

}
}

#endif