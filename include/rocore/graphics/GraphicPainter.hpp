//
// Created by mroszko on 10/24/2017.
//

#ifndef ROEDA_GRAPHICPAINTER_HPP
#define ROEDA_GRAPHICPAINTER_HPP

#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
	class ROCORE_EXPORT GraphicPainter {
	public:
		GraphicPainter() {
		}

		virtual ~GraphicPainter() {}

	public:
		virtual void DrawLine(Point& start, Point& end, double width) = 0;
		virtual void DrawCircle(Point& center, double radius, double holeRadius = 0.0, bool filled = false) = 0;
		virtual void DrawCartesianGrid(double minX, double maxX, double minY, double maxY, double xInterval, double yInterval) = 0;
		virtual void DrawArc(Point& center, double radius, double startAngle, double endAngle, double lineWidth, bool filled = false) = 0;
		virtual void DrawRectangle(Point& start, double xSize, double ySize) = 0;
	};
}
}


#endif //ROEDA_GRAPHICPAINTER_HPP
