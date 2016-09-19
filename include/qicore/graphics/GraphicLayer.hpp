//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GRAPHICLAYER_H
#define QIEDA_GRAPHICLAYER_H

#include <string>
#include <map>
#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/graphics/GLPainter.hpp"
#include "qicore/qicore.hpp"


namespace qicore {
namespace graphics {
    class GLPainter;
    class GraphicItem;


    class QICORE_EXPORT GraphicLayer {
    public:
        GraphicLayer(const Color& color) {};
        ~GraphicLayer();

        Color GetColor() const {
            return color_;
        }
        void SetColor(const Color& color);
        void Draw(GLPainter* painter);
        void AddItem(GraphicItem* item);

    private:
        Color color_;
        std::list<GraphicItem*> items_;
    };
}
}

#endif //QIEDA_GRAPHICLAYER_H
