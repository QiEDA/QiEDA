//
// Created by mroszko on 9/25/2016.
//

#ifndef QIEDA_GRIDLAYER_HPP
#define QIEDA_GRIDLAYER_HPP

#include "qicore/graphics/GraphicLayer.hpp"
#include "qicore/qicore.hpp"

namespace qicore {
namespace graphics {
    class QICORE_EXPORT GridLayer : public GraphicLayer {
    public:
        GridLayer() : GraphicLayer(Colors::DarkGray) {
        };
        virtual bool Prepare(GLPainter* painter) override;
    };
}
}


#endif //QIEDA_GRIDLAYER_HPP
