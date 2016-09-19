

#include "qicore/graphics/GraphicLayer.hpp"
using namespace qicore::graphics;

void GraphicLayer::SetColor(const Color& color)
{
    color_ = color;
}

void GraphicLayer::Draw(GLPainter* painter)
{
    for (auto it = items_.begin(); it != items_.end(); ++it) {
        (*it)->Draw(painter, color_);
    }
}

void GraphicLayer::AddItem(GraphicItem* item)
{
    items_.push_back(item);
}