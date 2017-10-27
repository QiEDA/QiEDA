//
// Created by mroszko on 10/24/2017.
//

#ifndef ROEDA_GRAPHICPAINTER_HPP
#define ROEDA_GRAPHICPAINTER_HPP

#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	class GraphicLine;
	class GraphicCircle;

	class ROCORE_EXPORT GraphicPainter {
	public:
		GraphicPainter() {
		}

		virtual ~GraphicPainter() {}

	public:
		virtual void DrawLine(Point& start, Point& end, double width) = 0;
		virtual void DrawCircle(Point& center, double radius) = 0;
	};
}
}


#endif //ROEDA_GRAPHICPAINTER_HPP
