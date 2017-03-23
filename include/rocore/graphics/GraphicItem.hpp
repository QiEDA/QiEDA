#ifndef __GRAPHIC_ITEM_HPP
#define __GRAPHIC_ITEM_HPP

#include "rocore/rocore.hpp"
#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GLPainter.hpp"
#include "rocore/graphics/BoundingBox.hpp"


namespace rocore {
namespace graphics {

class GLPainter;
class GraphicLayer;

class ROCORE_EXPORT GraphicItem {
public:
	GraphicItem() {
	}

	virtual ~GraphicItem() {}

	virtual void Draw(GraphicLayer* layer)  = 0;

	virtual BoundingBox GetBoundingBox() = 0;
protected:
};

}
}

#endif