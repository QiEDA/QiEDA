//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GRAPHICLAYER_H
#define QIEDA_GRAPHICLAYER_H

#include <string>
#include <vector>
#include <map>
#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/graphics/GLPainter.hpp"
#include "qicore/qicore.hpp"


namespace qicore {
namespace graphics {

    class GLPainter;
    class GraphicItem;

    enum GraphicPaintOperationType {
        GraphicPaintOperationQuad,
        GraphicPaintOperationLine
    };

    struct GraphicPaintOperation {
        GraphicPaintOperationType type;
        long offset;
        long vertexCount;
        Color fillColor;
    };


    class QICORE_EXPORT GraphicLayer {
    public:
        GraphicLayer(const Color& color);
        ~GraphicLayer();

        Color GetColor() const {
            return color_;
        }
        void SetColor(const Color& color);
     //   void Draw(GLPainter* painter);
        void AddItem(GraphicItem* item);

        void AddVertex(float x, float y, float z)
        {
            vertBuffer.push_back(x);
            vertBuffer.push_back(y);
            vertBuffer.push_back(z);
        }

        void AddOperation(GraphicPaintOperationType operation, int vertexCount)
        {
            long offset = vertBuffer.size() / 3;
            paintOperations.push_back({operation, offset, vertexCount, color_});
        }

        void Unprepare() {
            vertBuffer.clear();
        }

        const std::vector<float>& GetVertices()
        {
            return vertBuffer;
        }

        const std::vector<GraphicPaintOperation>& GetPaintOperations()
        {
            return paintOperations;
        }
        bool Prepare(GLPainter* painter);
    private:
        std::vector<float> vertBuffer;
        std::vector<GraphicPaintOperation> paintOperations;

        bool dirty_;
        Color color_;
        std::list<GraphicItem*> items_;
    };
}
}

#endif //QIEDA_GRAPHICLAYER_H
