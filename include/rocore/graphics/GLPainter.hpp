//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GLPAINTER_H
#define QIEDA_GLPAINTER_H

#include <string>
#include <map>
#include <list>
#include <memory>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "rocore/graphics/GLShader.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/graphics/GraphicLayer.hpp"
#include "rocore/graphics/GraphicPainter.hpp"
#include "rocore/graphics/GraphicDocument.hpp"
#include "rocore/graphics/Point.hpp"
#include "rocore/graphics/Color.hpp"
#include "rocore/rocore.hpp"

namespace rocore {
namespace graphics {
    class GraphicItem;
    class GraphicLayer;

    struct GLInstalledLayer {
        unsigned int arrayName;
        unsigned int bufferName;
        unsigned long int vertexCount;
        unsigned int paramsBufferName;
        unsigned int flagsBufferName;

    };

    class GLLayerBuildBuffer {
    public:
        const static GLint FilledCircle = (1 << 0);
        const static GLint HollowCircle = (1 << 1);
        const static GLint Line = (1 << 2);

        GLLayerBuildBuffer(double depth, Color color) : depth_(depth), color_(color){
        }

        void AddVertex(double x, double y) {
            vertBuffer_.push_back(x);
            vertBuffer_.push_back(y);
            vertBuffer_.push_back(depth_);

            flagsBuffer_.push_back(flags_);

            paramsBuffer_.push_back(paramA_);
            paramsBuffer_.push_back(paramB_);
            paramsBuffer_.push_back(paramC_);
            paramsBuffer_.push_back(paramD_);
        }

        void SetDepth(double depth) {
            depth_ = depth;
        }

        std::vector<double>& GetVerts() {
            return vertBuffer_;
        }

        std::vector<double>& GetParams() {
            return paramsBuffer_;
        }

        std::vector<GLint>& GetFlags() {
            return flagsBuffer_;
        }

        void SetFlags(GLint flags) {
            flags_ = flags;
        }

        void SetParams(double a, double b = 0.0, double c = 0.0, double d = 0.0) {
            paramA_ = a;
            paramB_ = b;
            paramC_ = c;
            paramD_ = d;
        }

    private:
        double depth_;
        Color color_;

        GLint flags_;
        double paramA_;
        double paramB_;
        double paramC_;
        double paramD_;

        std::vector<double> vertBuffer_;
        std::vector<double> paramsBuffer_;
        std::vector<GLint> flagsBuffer_;
    };

    class ROCORE_EXPORT GLPainter : GraphicPainter {
    public:
        GLPainter();
        ~GLPainter();
        void DrawLayer(GraphicLayer* layer);

        void Draw() ;
        void PrepareDraw(float panX, float panY, float zoom);
        void Resize(int w, int h);

        void SetDocument(GraphicDocument* document)
        {
            document_ = document;
        }

        glm::vec3 ScreenToWorldCoordinates(const glm::ivec2 &mouse, float z);
        void DrawLine(Point& start, Point& end, double width) override;
        void DrawCircle(Point& center, double radius) override;

    protected:
        void drawItems(GraphicLayer* layer, GLInstalledLayer* meta);

        void installGraphicLayer(GraphicLayer* layer);
        void uninstallGraphicLayer(GraphicLayer* layer);
    private:
        std::unique_ptr<GLLayerBuildBuffer> buildBuffer_;
        std::map<GraphicLayer*,GLInstalledLayer> installedLayers_;
        GLShader circleShader;
        GLShader generalShader;
        glm::mat4 projectionMatrix; // Store the projection matrix
        glm::mat4 viewMatrix; // Store the view matrix
        glm::mat4 modelMatrix; // Store the model matrix
        glm::mat4 modelViewProjectMatrix; // Store the model matrix

        GraphicDocument* document_;
    };
}
}

#endif //QIEDA_GLPAINTER_H
