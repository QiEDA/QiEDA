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

    class ROCORE_EXPORT GraphicLayer {
    public:
        GraphicLayer(const Color& color);
        virtual ~GraphicLayer()
        {

        }

        Color GetColor() const {
            return color_;
        }
        void SetColor(const Color& color);
        void AddItem(GraphicItem* item);

        void Unprepare() {
        }
        virtual bool Prepare(GLPainter* painter);

		bool IsDirty() const {
			return dirty_;
		}

		void ResetDirty() {
			dirty_ = false;
		}

		std::list<GraphicItem*>& GetItems() {
			return items_;
		}

		double GetDepth() {
			return depth_;
		}
    protected:
        bool dirty_;
        Color color_;
        std::list<GraphicItem*> items_;
        double depth_;
    };
}
}

#endif //QIEDA_GRAPHICLAYER_H
