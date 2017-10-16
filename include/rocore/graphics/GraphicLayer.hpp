//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GRAPHICLAYER_H
#define QIEDA_GRAPHICLAYER_H

#include <string>
#include <vector>
#include <map>
#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/graphics/GLPainter.hpp"
#include "rocore/rocore.hpp"


namespace rocore {
namespace graphics {

    class GLPainter;
    class GraphicItem;

    enum GraphicPaintOperationType {
		GraphicPaintOperationPoly,
        GraphicPaintOperationQuad,
        GraphicPaintOperationLine,
        GraphicPaintOperationTriangles,
		GraphicPaintOperationCircle
    };

    struct GraphicPaintOperation {
        GraphicPaintOperationType type;
        long offset;
        long vertexCount;
        Color fillColor;
        float lineWidth;
        float outerRadius;
        float innerRadius;
        double centerX;
        double centerY;
    };


    class ROCORE_EXPORT GraphicLayer {
    public:
        GraphicLayer(const Color& color);
        ~GraphicLayer();

        Color GetColor() const {
            return color_;
        }
        void SetColor(const Color& color);
        void AddItem(GraphicItem* item);

        void AddVertex(double x, double y)
        {
            vertBuffer_.push_back(x);
            vertBuffer_.push_back(y);
            vertBuffer_.push_back(depth_);
        }

        void AddOperation(GraphicPaintOperationType operation, int vertexCount, float lineWidth = 1, float outerRadius = 0.0, float innerRadius = 0.0, double centerX = 0.0, double centerY = 0.0)
        {
            long offset = vertBuffer_.size() / 3;
            paintOperations.push_back({operation, offset, vertexCount, color_, lineWidth,outerRadius, innerRadius, centerX, centerY});
        }

        void Unprepare() {
            vertBuffer_.clear();
        }

        const std::vector<double>& GetVertices()
        {
            return vertBuffer_;
        }

        const std::vector<GraphicPaintOperation>& GetPaintOperations()
        {
            return paintOperations;
        }
        virtual bool Prepare(GLPainter* painter);
    protected:
        std::vector<double> vertBuffer_;
        std::vector<GraphicPaintOperation> paintOperations;

        bool dirty_;
        Color color_;
        std::list<GraphicItem*> items_;
        double depth_;
    };
}
}

#endif //QIEDA_GRAPHICLAYER_H
