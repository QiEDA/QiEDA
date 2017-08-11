
#include <GL/glew.h>
#include <gl/GL.h>
#include "rocore/graphics/GraphicLayer.hpp"
using namespace rocore::graphics;

GraphicLayer::GraphicLayer(const Color& color)
{
    color_ = color;
    dirty_ = true;
    depth_ = 0;
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
    dirty_ = true;
}