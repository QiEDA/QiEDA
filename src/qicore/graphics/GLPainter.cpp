//
// Created by mroszko on 9/11/2016.
//

#include <iostream>
#include <GL/glew.h>
#include <gl/GL.h>
#include "qicore/Units.hpp"
#include "qicore/graphics/GLPainter.hpp"
#include "qicore/shaders/circle_vert.h"
#include "qicore/shaders/circle_frag.h"

using namespace qicore::graphics;


GLPainter::GLPainter() {
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        throw std::runtime_error( "glew failed to initialize!" );
    }

    circleShader.Load(circle_vert_shader, circle_frag_shader);
    circleShader.RegisterUniform("iCenter");

}

void GLPainter::DrawRect(const Point& start, float width, float height, const Color& color) {
    return;
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
    glVertex3f(start.x, start.y, 0.0);
    glVertex3f(end.x, end.y, 0);
    glEnd();
}


void GLPainter::DrawCircle(const Point& origin, float radius, const Color& color) {
    circleShader.Bind();


    glUniform2f(circleShader.GetUniformLocation("iCenter"), origin.x, origin.y);
    glColor4ub(color.red(), color.green(), color.blue(),color.alpha());
    glBegin(GL_QUADS);
    glVertex3f(origin.x-radius, origin.y-radius, 1);
    glVertex3f(origin.x+radius, origin.y-radius, 1);
    glVertex3f(origin.x+radius, origin.y+radius, 1);
    glVertex3f(origin.x-radius, origin.y+radius, 1);
    glEnd();

   circleShader.Unbind();
}


void GLPainter::Draw(std::list<GraphicItem*>& items) {
    drawGrid();

    for (auto it = items.begin(); it != items.end(); ++it) {
        (*it)->draw(this);
    }
}

void GLPainter::PrepareDraw(float panX, float panY, float zoom) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(panX,panY,0);
    glScalef(zoom,zoom,0);
}

void GLPainter::drawGrid() {
    int worldXMax = qicore::Units::MetersToInternalUnits(5);
    int worldXMin = -qicore::Units::MetersToInternalUnits(5);
    int worldYMax = qicore::Units::MetersToInternalUnits(5);
    int worldYMin = -qicore::Units::MetersToInternalUnits(5);
    Color gridColor = Colors::DimGray;

    glLineWidth(1);
    glColor3ub(gridColor.red(), gridColor.green(), gridColor.blue());
    for(float x = 0;x < worldXMax; x += qicore::Units::InchesToInternalUnits(0.1)) {
        glBegin(GL_LINES);
        glVertex3f(x, worldYMax, -1);
        glVertex3f(x, worldYMin, -1);
        glEnd();
    }

    for(float x = 0;x > worldXMin; x -= qicore::Units::InchesToInternalUnits(0.1)) {
        glBegin(GL_LINES);
        glVertex3f(x, worldYMax, -1);
        glVertex3f(x, worldYMin, -1);
        glEnd();
    }

    for(float y = 0;y < worldYMax; y += qicore::Units::InchesToInternalUnits(0.1)) {
        glBegin(GL_LINES);
        glVertex3f(worldXMax, y, 0);
        glVertex3f(worldXMin, y, 0);
        glEnd();
    }

    for(float y = 0;y > worldYMin; y -= qicore::Units::InchesToInternalUnits(0.1)) {
        glBegin(GL_LINES);
        glVertex3f(worldXMax, y, 0);
        glVertex3f(worldXMin, y, 0);
        glEnd();
    }

    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex3f(0, -qicore::Units::InchesToInternalUnits(1), 0);
    glVertex3f(0, qicore::Units::InchesToInternalUnits(1), 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-qicore::Units::InchesToInternalUnits(1), 0, 0);
    glVertex3f(qicore::Units::InchesToInternalUnits(1), 0, 0);
    glEnd();
}

void GLPainter::Resize(int w, int h)
{
    glViewport(0,0,w,h);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
}