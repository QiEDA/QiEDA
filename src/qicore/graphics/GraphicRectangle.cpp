
#include <gl/GL.h>
#include "qicore/graphics/GraphicRectangle.hpp"

using namespace qicore::graphics;

void GraphicRectangle::draw(GLPainter* painter)
{
    //nvgBeginPath(nvg);
    //nvgRect(nvg,start_.x,start_.y,width_,height_);
    //nvgFillColor(nvg, nvgRGBA(color_.red(),color_.green(),color_.blue(),color_.alpha()));
    //nvgFill(nvg);
/*
    glColor4ub(color_.red(), color_.green(), color_.blue(),color_.alpha());
    //glRectf(start_.x,start_.y, start_.x+width_,start_.y+height_);
    glBegin(GL_QUADS);
        glVertex3f(start_.x, start_.y, 1);
        glVertex3f(start_.x+width_, start_.y, 1);
        glVertex3f(start_.x+width_, start_.y+height_, 1);
        glVertex3f(start_.x, start_.y+height_, 1);
    glEnd();*/

    painter->DrawRect(start_, width_, height_, color_);
}


BoundingBox GraphicRectangle::GetBoundingBox()
{
    return BoundingBox(start_,width_,height_);
}