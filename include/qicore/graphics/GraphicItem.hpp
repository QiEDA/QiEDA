#ifndef __GRAPHIC_ITEM_HPP
#define __GRAPHIC_ITEM_HPP

#include "qicore/qicore.hpp"

struct NVGcontext;

namespace qicore {
namespace graphics {

struct QICORE_EXPORT Point {
	float x;
	float y;
};

class QICORE_EXPORT GraphicItem {
public:
	GraphicItem() {
	}

	virtual ~GraphicItem() {}

	virtual void draw(struct NVGcontext* nvg)  = 0;
};

}
}

#endif