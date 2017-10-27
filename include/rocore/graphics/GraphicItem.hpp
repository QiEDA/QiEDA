#ifndef __GRAPHIC_ITEM_HPP
#define __GRAPHIC_ITEM_HPP

#include "rocore/rocore.hpp"
#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GLPainter.hpp"
#include "rocore/graphics/BoundingBox.hpp"


namespace rocore {
namespace graphics {

class GLPainter;
class GraphicPainter;
class GraphicLayer;

class ROCORE_EXPORT GraphicItem {
public:
	GraphicItem() {
	}

	virtual ~GraphicItem() {}

	virtual void Draw(GraphicPainter* painter) {

	}

	virtual BoundingBox GetBoundingBox() = 0;
protected:
};

}
}

#endif