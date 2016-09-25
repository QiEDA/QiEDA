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
        float lineWidth;
    };


    class QICORE_EXPORT GraphicLayer {
    public:
        GraphicLayer(const Color& color);
        ~GraphicLayer();

        Color GetColor() const {
            return color_;
        }
        void SetColor(const Color& color);
        void AddItem(GraphicItem* item);

        void AddVertex(float x, float y)
        {
            vertBuffer_.push_back(x);
            vertBuffer_.push_back(y);
            vertBuffer_.push_back(depth_);
        }

        void AddOperation(GraphicPaintOperationType operation, int vertexCount, float lineWidth = 1)
        {
            long offset = vertBuffer_.size() / 3;
            paintOperations.push_back({operation, offset, vertexCount, color_, lineWidth});
        }

        void Unprepare() {
            vertBuffer_.clear();
        }

        const std::vector<float>& GetVertices()
        {
            return vertBuffer_;
        }

        const std::vector<GraphicPaintOperation>& GetPaintOperations()
        {
            return paintOperations;
        }
        virtual bool Prepare(GLPainter* painter);
    protected:
        std::vector<float> vertBuffer_;
        std::vector<GraphicPaintOperation> paintOperations;

        bool dirty_;
        Color color_;
        std::list<GraphicItem*> items_;
        float depth_;
    };
}
}

#endif //QIEDA_GRAPHICLAYER_H
