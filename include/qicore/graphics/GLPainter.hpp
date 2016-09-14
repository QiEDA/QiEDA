//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GLPAINTER_H
#define QIEDA_GLPAINTER_H

#include <string>
#include <map>
#include "qicore/graphics/GLShader.hpp"
#include "qicore/graphics/Point.hpp"
#include "qicore/graphics/Color.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
    class QICORE_EXPORT GLPainter {
    public:
        GLPainter();
        void DrawRect(const Point& start_, float width, float height, const Color& color);
        void DrawLine(const Point& start, const Point& end, float width, const Color& color);
    private:
         GLShader circleShader;
    };
}
}

#endif //QIEDA_GLPAINTER_H
