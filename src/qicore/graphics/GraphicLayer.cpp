
#include <GL/glew.h>
#include <gl/GL.h>
#include "qicore/graphics/GraphicLayer.hpp"
using namespace qicore::graphics;

GraphicLayer::GraphicLayer(const Color& color)
{
    color_ = color;
    dirty_ = true;
}

void GraphicLayer::SetColor(const Color& color)
{
    color_ = color;
}

bool GraphicLayer::Prepare(GLPainter* painter)
{
    if(dirty_)
    {
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            (*it)->Draw(this);
        }

        dirty_ = false;
        return true;
    }

    return false;
}

void GraphicLayer::AddItem(GraphicItem* item)
{
    items_.push_back(item);
}