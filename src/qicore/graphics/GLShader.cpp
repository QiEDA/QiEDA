//
// Created by mroszko on 9/13/2016.
//

#include <iostream>
#include <GL/glew.h>
#include <gl/GL.h>
#include "qicore/graphics/GLShader.hpp"
using namespace qicore::graphics;

GLShader::~GLShader() {
    if (programId != 0)
    {
        glDeleteProgram(programId);
    }
}

std::string GLShader::getShaderLog(int shader) {

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

std::string GLShader::getProgramLog(int shader) {

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

bool GLShader::Load(const char* vertexSrc, const char* fragmentSrc) {

    GLint status;
    GLuint prog = glCreateProgram();
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert, 1, &vertexSrc, NULL);
    glShaderSource(frag, 1, &fragmentSrc, NULL);

    glCompileShader(vert);
    glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::string err = getShaderLog(vert);
        std::cerr << "Error compiling vertex shader: " << std::endl << err;
        return false;
    }

    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::string err = getShaderLog(frag);
        std::cerr << "Error compiling fragment shader: " << std::endl << err;
        return false;
    }

    glAttachShader(prog, vert);
    glAttachShader(prog, frag);


    glLinkProgram(prog);
    glGetProgramiv(prog, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        std::string err = getProgramLog(prog);
        std::cerr << "Errorcreating shader program: " << std::endl << err;
        return false;
    }

    //delete the vert and frag reference, they won't actually delete until the program is deleted
    glDeleteShader(vert);
    glDeleteShader(frag);

    programId = prog;

    return true;
}


void GLShader::Bind() const {
    glUseProgram(programId);
}

void GLShader::Unbind() const{
    glUseProgram(0);
}


void GLShader::RegisterAttribute(const char* attribute){
    attributeList_[attribute] = glGetAttribLocation(programId, attribute);
}

void GLShader::RegisterUniform(const char* uniform){
    uniformList_[uniform] = glGetUniformLocation(programId, uniform);
}

unsigned int GLShader::GetAttribLocation(const char* attribute){
    return attributeList_[attribute];
}

unsigned int GLShader::GetUniformLocation(const char* uniform){
    return uniformList_[uniform];
}