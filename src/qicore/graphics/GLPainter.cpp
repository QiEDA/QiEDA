//
// Created by mroszko on 9/11/2016.
//

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <gl/GL.h>
#include "qicore/Units.hpp"
#include "qicore/graphics/GLPainter.hpp"
#include "qicore/shaders/circle_vert.h"
#include "qicore/shaders/circle_frag.h"
#include "qicore/shaders/shader_vert.h"
#include "qicore/shaders/shader_frag.h"

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

    generalShader.Load(shader_vert_shader, shader_frag_shader);
    generalShader.BindAttributeLocation("vi_VertexPos",0);
 //   generalShader.BindAttributeLocation("vi_Color",1);
    generalShader.RegisterUniform("projectionMatrix");
    generalShader.RegisterUniform("viewMatrix");
    generalShader.RegisterUniform("modelMatrix");
    generalShader.RegisterUniform("vi_Color");


    prepareGrid();
}

void GLPainter::DrawRect(const Point& start, float width, float height, const Color& color) {
    glUniform4f(generalShader.GetUniformLocation("vi_Color"), color.redf(), color.greenf(), color.bluef(), color.alphaf());

    glBegin(GL_QUADS);
    glVertex3f(start.x, start.y, 1);
    glVertex3f(start.x+width, start.y, 1);
    glVertex3f(start.x+width, start.y+height, 1);
    glVertex3f(start.x, start.y+height, 1);
    glEnd();
}

void GLPainter::DrawLine(const Point& start, const Point& end, float width, const Color& color) {
    glLineWidth(width);
    glUniform4f(generalShader.GetUniformLocation("vi_Color"), color.redf(), color.greenf(), color.bluef(), color.alphaf());
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, 0.0);
    glVertex3f(end.x, end.y, 0);
    glEnd();
}


void GLPainter::DrawCircle(const Point& origin, float radius, const Color& color) {

    generalShader.Unbind();
    circleShader.Bind();

    glUniform2f(circleShader.GetUniformLocation("iCenter"), origin.x, origin.y);
    glUniform4f(generalShader.GetUniformLocation("vi_Color"), color.redf(), color.greenf(), color.bluef(), color.alphaf());
    glBegin(GL_QUADS);
    glVertex3f(origin.x-radius, origin.y-radius, 0);
    glVertex3f(origin.x+radius, origin.y-radius, 0);
    glVertex3f(origin.x+radius, origin.y+radius, 0);
    glVertex3f(origin.x-radius, origin.y+radius, 0);
    glEnd();

    circleShader.Unbind();
    generalShader.Bind();
}


void GLPainter::Draw(std::list<GraphicLayer*>& items) {
    drawGrid();

    for (auto it = items.begin(); it != items.end(); ++it) {
        (*it)->Draw(this);
    }
}

void GLPainter::PrepareDraw(float panX, float panY, float zoom) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(panX, panY, 0.0f));
    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(zoom));

    generalShader.Bind();
    //push the transformation matrices into the general shader
    glUniformMatrix4fv(generalShader.GetUniformLocation("projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(generalShader.GetUniformLocation("viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(generalShader.GetUniformLocation("modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
}

void GLPainter::gridCleanup() {
    if(gridVbo != 0)
    {
        glDeleteBuffers(1, &gridVbo);
    }

    if(gridVao != 0)
    {
        glDeleteVertexArrays(1, &gridVao);
    }
}

void GLPainter::prepareGrid() {
    gridCleanup();

    /* square grid so min and max are identical for X and Y */
    float max = qicore::Units::MetersToInternalUnits(1);
    float majorIncrement  = qicore::Units::MillimetersToInternalUnits(10);

    //total lines
    long axisHalfLines =  std::floor(max/majorIncrement);
    long axisHalfVerts = axisHalfLines*2;
    long totalVerts = axisHalfVerts*4;

    glGenVertexArrays(1, &gridVao);
    glBindVertexArray(gridVao);

    std::vector<GLfloat> verts;
    verts.reserve(totalVerts);

    max -= majorIncrement;  //decrement the max by the increment to "cap" off the ends
    for(int i = 0;i < axisHalfLines; i++) {
        GLfloat pos = i*majorIncrement;
        verts.push_back(pos);
        verts.push_back(max);
        verts.push_back(0);

        verts.push_back(pos);
        verts.push_back(-max);
        verts.push_back(0);

        verts.push_back(-pos);
        verts.push_back(max);
        verts.push_back(0);

        verts.push_back(-pos);
        verts.push_back(-max);
        verts.push_back(0);

        verts.push_back(max);
        verts.push_back(pos);
        verts.push_back(0);

        verts.push_back(-max);
        verts.push_back(pos);
        verts.push_back(0);

        verts.push_back(max);
        verts.push_back(-pos);
        verts.push_back(0);

        verts.push_back(-max);
        verts.push_back(-pos);
        verts.push_back(0);
    }


    glGenBuffers(1, &gridVbo);
    glBindBuffer(GL_ARRAY_BUFFER, gridVbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(GLfloat), &verts[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);;

    glBindVertexArray(0);

    totalGridVerts_ = totalVerts;
}

void GLPainter::drawGrid() {
    Color gridColor = Colors::DimGray;
    glUniform4f(generalShader.GetUniformLocation("vi_Color"), gridColor.redf(), gridColor.greenf(), gridColor.bluef(), gridColor.alphaf());
    glBindVertexArray (gridVao);
    glDrawArrays (GL_LINES, 0, totalGridVerts_);
    glBindVertexArray(0);
    return;
}

void GLPainter::Resize(int w, int h)
{
    glViewport(0,0,w,h);

    projectionMatrix = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
}