//
// Created by mroszko on 9/11/2016.
//

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <gl/GL.h>
#include "rocore/Units.hpp"
#include "rocore/graphics/GLPainter.hpp"
#include "rocore/shaders/shader_vert.h"
#include "rocore/shaders/shader_frag.h"

using namespace rocore::graphics;


GLPainter::GLPainter() {
    glClearColor(0,0,0,1);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        throw std::runtime_error( "glew failed to initialize!" );
    }

    generalShader.Load(shader_vert_shader, shader_frag_shader);
    generalShader.BindAttributeLocation("vi_VertexPos",0);
    generalShader.RegisterUniform("projectionMatrix");
    generalShader.RegisterUniform("viewMatrix");
    generalShader.RegisterUniform("modelMatrix");
	generalShader.RegisterUniform("mvpMatrix");
    generalShader.RegisterUniform("vi_Color");
	generalShader.RegisterUniform("un_OuterRadius");
	generalShader.RegisterUniform("un_Options");
	generalShader.RegisterUniform("un_Center");
}

GLPainter::~GLPainter()
{
    for (auto it = registeredLayers_.begin(); it != registeredLayers_.end(); ++it) {
        UnregisterGraphicLayer(it->first);
    }
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
        glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(GLdouble), &verts[0], GL_STREAM_DRAW);
        glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);;
    }

    glEnableVertexAttribArray(0);

    auto paintOperations = layer->GetPaintOperations();
    for(auto cmd : paintOperations)
    {
		glUniform4f(generalShader.GetUniformLocation("vi_Color"), cmd.fillColor.redf(), cmd.fillColor.greenf(), cmd.fillColor.bluef(), cmd.fillColor.alphaf());
		if(cmd.type == GraphicPaintOperationCircle)
		{
			glUniform1f(generalShader.GetUniformLocation("un_OuterRadius"),Units::MilsToInternalUnits(250));
			glUniform2f(generalShader.GetUniformLocation("un_Center"),cmd.centerX, cmd.centerY);
			glUniform1i(generalShader.GetUniformLocation("un_Options"),(1 << 0));
		}
		else
		{
			glUniform1i(generalShader.GetUniformLocation("un_Options"),0);
		}

        if(cmd.type == GraphicPaintOperationLine)
        {
            glLineWidth(cmd.lineWidth);
            glDrawArrays(GL_LINES, cmd.offset, cmd.vertexCount);
        }
        else if(cmd.type == GraphicPaintOperationTriangles || cmd.type == GraphicPaintOperationCircle)
        {
            glDrawArrays(GL_TRIANGLES, cmd.offset, cmd.vertexCount);
        }
        else if(cmd.type == GraphicPaintOperationQuad)
        {
            glDrawArrays(GL_QUADS, cmd.offset, cmd.vertexCount);
        }
		else if(cmd.type == GraphicPaintOperationPoly)
		{
			glDrawArrays(GL_POLYGON, cmd.offset, cmd.vertexCount);
		}
    }

    layer->Unprepare();

    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void GLPainter::PrepareDraw(float panX, float panY, float zoom) {
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(panX, panY, 0.0f));
    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(zoom));
	modelViewProjectMatrix =  projectionMatrix * viewMatrix * modelMatrix;

    generalShader.Bind();
    //push the transformation matrices into the general shader
	glUniformMatrix4fv(generalShader.GetUniformLocation("mvpMatrix"), 1, GL_FALSE, &modelViewProjectMatrix[0][0]); // Send our projection matrix to the shader
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


glm::vec3 GLPainter::ScreenToWorldCoordinates(const glm::ivec2 &screenCoord, float z)
{
	//x,y,width,height
	GLint viewportRaw[4];
	glGetIntegerv( GL_VIEWPORT, viewportRaw );

	glm::vec2 offset = glm::vec2(viewportRaw[0],viewportRaw[1]);
	glm::vec2 size = glm::vec2(viewportRaw[2],viewportRaw[3]);

	glm::vec4 viewport = glm::vec4( offset.x, offset.y,  size.x, size.y );

	// Calculate the view-projection matrix.
	glm::mat4 transform = projectionMatrix * viewMatrix;


	glm::vec3 near = glm::unProject( glm::vec3( screenCoord.x, size.y - screenCoord.y, 0 ), glm::mat4(), transform, viewport );
	glm::vec3 far = glm::unProject(  glm::vec3( screenCoord.x, size.y - screenCoord.y, 1 ), glm::mat4(), transform, viewport );

	// Calculate world position.
	return glm::mix( near, far, ( z - near.z ) / ( far.z - near.z ) );
}