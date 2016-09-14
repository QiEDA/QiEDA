//
// Created by mroszko on 9/11/2016.
//

#ifndef QIEDA_GLSHADER_H
#define QIEDA_GLSHADER_H

#include <string>
#include <map>
#include "qicore/graphics/Point.hpp"
#include "qicore/graphics/Color.hpp"
#include "qicore/qicore.hpp"


namespace qicore {
namespace graphics {
    class QICORE_EXPORT GLShader {
    public:
        GLShader() {};
        ~GLShader();
        bool Load(const char* vertexSrc, const char* fragmentSrc);
        void Bind() const;
        void Unbind() const;

        void RegisterAttribute(const char* attribute);
        void RegisterUniform(const char* uniform);
        unsigned int GetAttribLocation(const char* attribute);
        unsigned int GetUniformLocation(const char* uniform);

        unsigned int ProgramId() const {
            return programId;
        }
    private:
        unsigned int programId;
        std::string getShaderLog(int shader);
        std::string getProgramLog(int shader);
        std::map<std::string, unsigned int> attributeList_;
        std::map<std::string, unsigned int> uniformList_;
    };
}
}

#endif //QIEDA_GLSHADER_H
