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
	std::vector<Point> points_;
public:
	GraphicPoly(std::vector<Point>& points) : GraphicItem() {
		points_ = points;
	}

	BoundingBox GetBoundingBox() override;
	void Draw(GraphicPainter* painter) override;
};

}
}

#endif //ROEDA_GRAPHICPOLY_HPP


