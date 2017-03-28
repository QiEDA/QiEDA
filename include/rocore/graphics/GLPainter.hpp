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
#include "rocore/graphics/GLShader.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/graphics/GraphicLayer.hpp"
#include "rocore/graphics/Point.hpp"
#include "rocore/graphics/Color.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
    class GraphicItem;
    class GraphicLayer;

    struct GLLayerMeta {
        unsigned int arrayName;
        unsigned int bufferName;
    };

    class ROCORE_EXPORT GLPainter {
    public:
        GLPainter();
        ~GLPainter();
        void DrawLayer(GraphicLayer* layer);

        void Draw() ;
        void PrepareDraw(float panX, float panY, float zoom);
        void Resize(int w, int h);

        void RegisterGraphicLayer(GraphicLayer* layer);
        void UnregisterGraphicLayer(GraphicLayer* layer);
    private:
        std::map<GraphicLayer*,GLLayerMeta> registeredLayers_;
        GLShader circleShader;
        GLShader generalShader;
        glm::mat4 projectionMatrix; // Store the projection matrix
        glm::mat4 viewMatrix; // Store the view matrix
        glm::mat4 modelMatrix; // Store the model matrix
    };
}
}

#endif //QIEDA_GLPAINTER_H
