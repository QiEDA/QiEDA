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
    CreateShader("circle", circle_vert_shader, circle_frag_shader);
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

std::string GLPainter::getShaderLog(int shader) {

    GLchar str[1024+1];
    GLsizei len = 0;
    GLsizei maxLen = sizeof(str)-1;
    glGetShaderInfoLog(shader, maxLen, &len, str);
    if (len > maxLen)
    {
        len = maxLen;
    }
    str[len] = '\0';

    return std::string(str);
}

std::string GLPainter::getProgramLog(int shader) {

    GLchar str[1024+1];
    GLsizei len = 0;
    GLsizei maxLen = sizeof(str)-1;
    glGetProgramInfoLog(shader,maxLen, &len, str);
    if (len > maxLen)
    {
        len = maxLen;
    }
    str[len] = '\0';

    return std::string(str);
}

bool GLPainter::CreateShader(const std::string& name, const char* vertexSrc, const char* fragmentSrc) {

    GLint status;
    GLuint prog = glCreateProgram();
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert, 1, &vertexSrc, NULL);
    glShaderSource(frag, 1, &fragmentSrc, NULL);

    glCompileShader(vert);
    glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cerr << "Error compiling vertex shader: " << name;
        std::cerr << getShaderLog(vert);
        return false;
    }

    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cerr << "Error compiling fragment shader: " << name;
        std::cerr << getShaderLog(vert);
        return false;
    }

    glAttachShader(prog, vert);
    glAttachShader(prog, frag);


    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        std::cerr << "Error creating shader program:" << name;
        std::cerr << getProgramLog(vert);
        return false;
    }

    shaderMap_.insert(std::pair<std::string,int>(name, prog));

    return true;
}

bool GLPainter::UseShader(const std::string& name)
{
    auto it = shaderMap_.find(name);
    if(it != shaderMap_.end()){
        glUseProgram(it->second);
        return true;
    }

    return false;
}