//
// Created by mroszko on 3/27/2017.
//

#ifndef ROEDA_GRAPHICPOLY_HPP
#define ROEDA_GRAPHICPOLY_HPP

#include <list>
#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {

class ROCORE_EXPORT GraphicPoly : public GraphicItem {
protected:
	std::list<Point> points_;
public:
	GraphicPoly(std::list<Point>& points) : GraphicItem() {
		points_ = points;
	}

	void Draw(GraphicLayer* layer) override;

	BoundingBox GetBoundingBox() override;
};

}
}

#endif //ROEDA_GRAPHICPOLY_HPP


