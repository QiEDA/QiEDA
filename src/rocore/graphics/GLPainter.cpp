//
// Created by mroszko on 9/11/2016.
//

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <gl/GL.h>
#include "rocore/Units.hpp"
#include "rocore/graphics/GLPainter.hpp"
#include "rocore/shaders/circle_vert.h"
#include "rocore/shaders/circle_frag.h"
#include "rocore/shaders/shader_vert.h"
#include "rocore/shaders/shader_frag.h"

using namespace rocore::graphics;


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
}

GLPainter::~GLPainter()
{
    for (auto it = registeredLayers_.begin(); it != registeredLayers_.end(); ++it) {
        UnregisterGraphicLayer(it->first);
    }
}

void GLPainter::DrawRect(const Point& start, float width, float height, const Color& color) {
    glUniform4f(generalShader.GetUniformLocation("vi_Color"), color.redf(), color.greenf(), color.bluef(), color.alphaf());

   /*
    glBegin(GL_QUADS);
    glVertex3f(start.x, start.y, 1);
    glVertex3f(start.x+width, start.y, 1);
    glVertex3f(start.x+width, start.y+height, 1);
    glVertex3f(start.x, start.y+height, 1);
    glEnd();
    */
    GLfloat verts[4][3]  = {
            {start.x,start.y,0},
            {start.x+width, start.y, 0},
            {start.x+width, start.y+height, 0},
            {start.x, start.y+height, 0}
    };

    unsigned int rectVbo;
    glGenBuffers(1, &rectVbo);
    glBindBuffer(GL_ARRAY_BUFFER, rectVbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);;
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


void GLPainter::Draw() {
    for (auto it = registeredLayers_.begin(); it != registeredLayers_.end(); ++it) {
        DrawLayer(it->first);
    }
}

void GLPainter::DrawLayer(GraphicLayer* layer) {

    GLLayerMeta* meta = &registeredLayers_[layer];

    glBindVertexArray(meta->arrayName);
    glBindBuffer(GL_ARRAY_BUFFER, meta->bufferName);

    if(layer->Prepare(this))
    {
        auto verts = layer->GetVertices();
        glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(GLfloat), &verts[0], GL_STREAM_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);;
    }

    glEnableVertexAttribArray(0);

    auto paintOperations = layer->GetPaintOperations();
    for(auto cmd : paintOperations)
    {
        glUniform4f(generalShader.GetUniformLocation("vi_Color"), cmd.fillColor.redf(), cmd.fillColor.greenf(), cmd.fillColor.bluef(), cmd.fillColor.alphaf());
        if(cmd.type == GraphicPaintOperationLine)
        {
            glLineWidth(cmd.lineWidth);
            glDrawArrays(GL_LINES, cmd.offset, cmd.vertexCount);
        }
        else if(cmd.type == GraphicPaintOperationQuad)
        {
            glDrawArrays(GL_QUADS, cmd.offset, cmd.vertexCount);
        }
    }

    layer->Unprepare();

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
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


void GLPainter::Resize(int w, int h)
{
    glViewport(0,0,w,h);

    projectionMatrix = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
}


void GLPainter::RegisterGraphicLayer(GraphicLayer* layer)
{
    auto l = registeredLayers_.find(layer);

    if(l == registeredLayers_.end()) {
        GLLayerMeta meta;
        glGenVertexArrays(1, &meta.arrayName);
        glGenBuffers(1, &meta.bufferName);

        registeredLayers_[layer] = meta;
    }
}

void GLPainter::UnregisterGraphicLayer(GraphicLayer* layer)
{
    GLLayerMeta* meta = &registeredLayers_[layer];
    if(meta->bufferName != 0)
    {
        glDeleteBuffers(1, &meta->bufferName);
    }

    if(meta->arrayName != 0)
    {
        glDeleteVertexArrays(1, &meta->arrayName);
    }

    registeredLayers_.erase(layer);
}