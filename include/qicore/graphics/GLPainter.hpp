//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GLPAINTER_H
#define QIEDA_GLPAINTER_H

#include <string>
#include <map>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "qicore/graphics/GLShader.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/graphics/Point.hpp"
#include "qicore/graphics/Color.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
    class GraphicItem;

    class QICORE_EXPORT GLPainter {
    public:
        GLPainter();
        void DrawRect(const Point& start_, float width, float height, const Color& color);
        void DrawLine(const Point& start, const Point& end, float width, const Color& color);
        void DrawCircle(const Point& origin, float radius, const Color& color);

        void Draw(std::list<GraphicItem*>& items);
        void PrepareDraw(float panX, float panY, float zoom);
        void Resize(int w, int h);
    private:
        GLShader circleShader;
        GLShader generalShader;
        void drawGrid();
        glm::mat4 projectionMatrix; // Store the projection matrix
        glm::mat4 viewMatrix; // Store the view matrix
        glm::mat4 modelMatrix; // Store the model matrix
    };
}
}

#endif //QIEDA_GLPAINTER_H
