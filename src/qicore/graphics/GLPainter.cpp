//
// Created by mroszko on 9/11/2016.
//

#include <gl/GL.h>
#include "qicore/graphics/GLPainter.hpp"

using namespace qicore::graphics;

void GLPainter::DrawRect(const Point& start, float width, float height, const Color& color) {
    glColor4ub(color.red(), color.green(), color.blue(),color.alpha());
    glBegin(GL_QUADS);
    glVertex3f(start.x, start.y, 1);
    glVertex3f(start.x+width, start.y, 1);
    glVertex3f(start.x+width, start.y+height, 1);
    glVertex3f(start.x, start.y+height, 1);
    glEnd();
}

void GLPainter::DrawLine(const Point& start, const Point& end, float width, const Color& color) {
    glLineWidth(width);
    glColor4ub(color.red(), color.green(), color.blue(),color.alpha());
    glBegin(GL_LINES);
    glVertex3f(start.x, start.x, 0.0);
    glVertex3f(end.x, end.y, 0);
    glEnd();
}
