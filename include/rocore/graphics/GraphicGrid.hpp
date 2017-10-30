//
// Created by mroszko on 10/28/2017.
//

#ifndef ROEDA_GRAPHICGRID_HPP
#define ROEDA_GRAPHICGRID_HPP


#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {

	class ROCORE_EXPORT GraphicGrid : public GraphicItem {

	public:
		GraphicGrid() : GraphicItem() {
		}

		void Draw(GraphicPainter* painter) override;


		BoundingBox GetBoundingBox() override {
			Point start;
			start.x = 0;
			start.y = 0;

			return BoundingBox(start,0,0);
		}
	};

}
}


#endif //ROEDA_GRAPHICGRID_HPP
