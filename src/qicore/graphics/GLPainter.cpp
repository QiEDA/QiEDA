//
// Created by mroszko on 9/11/2016.
//

#include <iostream>
#include <GL/glew.h>
#include <gl/GL.h>
#include "qicore/graphics/GLPainter.hpp"
#include "qicore/shaders/circle_vert.h"
#include "qicore/shaders/circle_frag.h"

using namespace qicore::graphics;


GLPainter::GLPainter() {
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        throw std::runtime_error( "glew failed to initialize!" );
    }
    //CreateShader("circle", circle_vert_shader, circle_frag_shader);
    circleShader.Load(circle_vert_shader, circle_frag_shader);
}

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
