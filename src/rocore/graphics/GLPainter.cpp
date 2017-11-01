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


GLPainter::GLPainter() : GraphicPainter() {
    glClearColor(0,0,0,1);

    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        throw std::runtime_error( "glew failed to initialize!" );
    }

    generalShader.Load(shader_vert_shader, shader_frag_shader);
    generalShader.RegisterAttribute("vi_VertexPos");
	generalShader.RegisterAttribute("vi_Params");
	generalShader.RegisterAttribute("vi_Flags");
    generalShader.RegisterUniform("projectionMatrix");
    generalShader.RegisterUniform("viewMatrix");
    generalShader.RegisterUniform("modelMatrix");
	generalShader.RegisterUniform("mvpMatrix");
    generalShader.RegisterUniform("vi_Color");
}

GLPainter::~GLPainter()
{
    for (auto it = installedLayers_.begin(); it != installedLayers_.end(); ++it) {
        uninstallGraphicLayer(it->first);
    }
}

void GLPainter::DrawLine(Point& start, Point& end, double width) {
	// Get the normal of the line
	double dx = end.x - start.x;
	double dy = end.y - start.y;

	width /= 2;

	auto normal = glm::normalize(glm::highp_dvec2(-dy, dx));

	//use the normal to calculate the locations of the vertices of the line being drawn as a narrow rectangle
	//setup for triangle fan
	auto pointA = glm::highp_dvec2(start.x,start.y) - (normal * width);
	auto pointB = glm::highp_dvec2(start.x,start.y) + (normal * width);
	auto pointC = glm::highp_dvec2(end.x,end.y) - (normal * width);
	auto pointD = glm::highp_dvec2(end.x,end.y) + (normal * width);
	/*
	 * Split into two triangles
	 * start
	 * A-------------B
	 * |          /  |
	 * |        /    |
	 * |      /      |
	 * |    /        |
	 * |  /          |
	 * |/            |
	 * C-------------D
	 * end
	 */

	buildBuffer_->SetFlags(GLLayerBuildBuffer::Line);
	buildBuffer_->SetParams(width);
	buildBuffer_->AddVertex(pointA.x, pointA.y);
	buildBuffer_->AddVertex(pointB.x, pointB.y);
	buildBuffer_->AddVertex(pointC.x, pointC.y);

	buildBuffer_->AddVertex(pointC.x, pointC.y);
	buildBuffer_->AddVertex(pointD.x, pointD.y);
	buildBuffer_->AddVertex(pointB.x, pointB.y);
}

void GLPainter::DrawCircle(Point& center, double radius, bool filled) {
	/*
	 * Split into two triangles
	 * *-------------*
	 * | \           |
	 * |   \         |
	 * |     \       |
	 * |       \     |
	 * |         \   |
	 * |           \ |
	 * *-------------*
	 */

	buildBuffer_->SetFlags(GLLayerBuildBuffer::FilledCircle);
	buildBuffer_->SetParams(center.x, center.y, radius);	//centerx, centery, outer radius, inner radius?

	buildBuffer_->AddVertex(center.x - radius, center.y + radius); //upper left corner
	buildBuffer_->AddVertex(center.x - radius, center.y - radius); //bottom left corner
	buildBuffer_->AddVertex(center.x + radius, center.y - radius); //bottom right corner
	buildBuffer_->AddVertex(center.x + radius, center.y - radius); //bottom right corner
	buildBuffer_->AddVertex(center.x + radius, center.y + radius); //upper right corner
	buildBuffer_->AddVertex(center.x - radius, center.y + radius); //upper left corner
}

void GLPainter::DrawCartesianGrid(double minX, double maxX, double minY, double maxY, double xInterval, double yInterval)
{
	buildBuffer_->SetFlags(GLLayerBuildBuffer::CartesianGrid);
	buildBuffer_->SetParams(xInterval, yInterval);
	buildBuffer_->AddVertex(minX, minY);
	buildBuffer_->AddVertex(minX, maxY);
	buildBuffer_->AddVertex(maxX, minY);

	buildBuffer_->AddVertex(maxX, minY);
	buildBuffer_->AddVertex(minX, maxY);
	buildBuffer_->AddVertex(maxX, maxY);
}

void GLPainter::DrawArc(Point& center, double radius, double startAngle, double endAngle, double lineWidth, bool filled)
{
	//make sure angles are positive
	while (startAngle < 0) {
		startAngle += 2*M_PI;
	}

	while (endAngle < 0) {
		endAngle += 2*M_PI;
	}

	startAngle = fmod(startAngle,2*M_PI);
	endAngle = fmod(endAngle,2*M_PI);

	if (endAngle == startAngle) {
		endAngle += 2*M_PI;
	}

	double increment = (endAngle-startAngle)/160;

	double theta;
	/*
	if(filled) {
		Point p1;
		p1.x = (radius * cos(startAngle)) + center.x;
		p1.y = (radius * sin(startAngle)) + center.y;

		for (theta = startAngle + increment; theta <= endAngle; theta += increment) {
			Point p2;

			p2.x = (radius * cos(theta)) + center.x;
			p2.y = (radius * sin(theta)) + center.y;

			DrawLine(p1, p2, lineWidth);

			p1 = p2;
		}

		if(theta != endAngle) {
			Point p2;

			p2.x = (radius * cos(endAngle)) + center.x;
			p2.y = (radius * sin(endAngle)) + center.y;

			DrawLine(p1, p2, lineWidth);
		}
	} else {*/
		if(filled) {
			buildBuffer_->SetFlags(GLLayerBuildBuffer::FilledArc);
		} else {
			buildBuffer_->SetFlags(GLLayerBuildBuffer::LineArc);
		}
		buildBuffer_->SetParams(center.x,center.y, radius+lineWidth/2, radius-lineWidth/2);
		for(theta = startAngle; (theta+increment) < endAngle; ){

			buildBuffer_->AddVertex(center.x, center.y);
			buildBuffer_->AddVertex((radius * cos(theta)) + center.x, (radius * sin(theta)) + center.y);
			theta += increment;
			buildBuffer_->AddVertex((radius * cos(theta)) + center.x, (radius * sin(theta)) + center.y);
		}

		buildBuffer_->AddVertex(center.x, center.y); //upper left corner
		buildBuffer_->AddVertex((radius * cos(theta)) + center.x, (radius * sin(theta)) + center.y);
		buildBuffer_->AddVertex((radius * cos(endAngle)) + center.x, (radius * sin(endAngle)) + center.y);
	//}
}

void GLPainter::Draw() {
	//dont crash
	if(document_ == nullptr) {
		return;
	}

	auto layers = document_->GetLayers();
    for (auto layer : layers) {
        DrawLayer(layer);
    }
}


void GLPainter::drawItems(GraphicLayer* layer, GLInstalledLayer* meta) {
	auto items = layer->GetItems();

	for (auto item : items) {
		item->Draw(this);
	}

	auto verts = buildBuffer_->GetVerts();
	glBindBuffer(GL_ARRAY_BUFFER, meta->bufferName);
	glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(GLdouble), verts.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(generalShader.GetAttribLocation("vi_VertexPos"), 3, GL_DOUBLE, GL_FALSE, 0, 0);

	auto params = buildBuffer_->GetParams();
	glBindBuffer(GL_ARRAY_BUFFER, meta->paramsBufferName);
	glBufferData(GL_ARRAY_BUFFER, params.size()*sizeof(GLdouble), params.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(generalShader.GetAttribLocation("vi_Params"), 4, GL_DOUBLE, GL_FALSE, 0, 0);

	auto flags = buildBuffer_->GetFlags();
	glBindBuffer(GL_ARRAY_BUFFER, meta->flagsBufferName);
	glBufferData(GL_ARRAY_BUFFER, flags.size()*sizeof(GL_INT), flags.data(), GL_STATIC_DRAW);
	glVertexAttribIPointer(generalShader.GetAttribLocation("vi_Flags"), 1, GL_INT, 0, 0);


	glEnableVertexAttribArray(generalShader.GetAttribLocation("vi_VertexPos"));
	glEnableVertexAttribArray(generalShader.GetAttribLocation("vi_Params"));
	glEnableVertexAttribArray(generalShader.GetAttribLocation("vi_Flags"));

	meta->vertexCount = verts.size();
}

void GLPainter::DrawLayer(GraphicLayer* layer) {

	//layer isn't cached yet?
	if(installedLayers_.find(layer) == installedLayers_.end()) {
		installGraphicLayer(layer);
	}
	GLInstalledLayer* meta = &installedLayers_[layer];

	glBindVertexArray(meta->arrayName);

    if(layer->IsDirty())
    {
		buildBuffer_.reset(new GLLayerBuildBuffer(layer->GetDepth(), layer->GetColor()));
		drawItems(layer, meta);
		layer->ResetDirty();
		buildBuffer_.release();
    }

	auto color = layer->GetColor();
	glUniform4f(generalShader.GetUniformLocation("vi_Color"), color.redf(), color.greenf(), color.bluef(), color.alphaf());
	glDrawArrays(GL_TRIANGLES, 0, meta->vertexCount);
	/*
		if(cmd.type == GraphicPaintOperationRawLine)
		{
			glLineWidth(1.0);
			glDrawArrays(GL_LINES, cmd.offset, cmd.vertexCount);
		}
    }
*/
    layer->Unprepare();

    glBindVertexArray(0);
}

void GLPainter::PrepareDraw(float panX, float panY, float zoom) {
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	glDisable(GL_CULL_FACE);

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	glEnable( GL_BLEND );
	//Per Khronos notes: Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest.
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(panX, panY, 0.0f));
    modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, 0.0f));
	modelViewProjectMatrix =  projectionMatrix * viewMatrix * modelMatrix;

    generalShader.Bind();

	glUniformMatrix4fv(generalShader.GetUniformLocation("mvpMatrix"), 1, GL_FALSE, &modelViewProjectMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(generalShader.GetUniformLocation("projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(generalShader.GetUniformLocation("viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(generalShader.GetUniformLocation("modelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
}


void GLPainter::Resize(int w, int h)
{
    glViewport(0,0,w,h);

    projectionMatrix = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -100.0f, 100.0f);
}


void GLPainter::installGraphicLayer(GraphicLayer* layer)
{
    auto l = installedLayers_.find(layer);

    if(l == installedLayers_.end()) {
		GLInstalledLayer meta;
        glGenVertexArrays(1, &meta.arrayName);
        glGenBuffers(1, &meta.bufferName);
		glGenBuffers(1, &meta.paramsBufferName);
		glGenBuffers(1, &meta.flagsBufferName);

		installedLayers_[layer] = meta;
    }
}

void GLPainter::uninstallGraphicLayer(GraphicLayer* layer)
{
	GLInstalledLayer* meta = &installedLayers_[layer];
    if(meta->bufferName != 0)
    {
        glDeleteBuffers(1, &meta->bufferName);
    }

	if(meta->flagsBufferName != 0)
	{
		glDeleteBuffers(1, &meta->flagsBufferName);
	}

	if(meta->paramsBufferName != 0)
	{
		glDeleteBuffers(1, &meta->paramsBufferName);
	}

	if(meta->arrayName != 0)
    {
        glDeleteVertexArrays(1, &meta->arrayName);
    }

	installedLayers_.erase(layer);
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