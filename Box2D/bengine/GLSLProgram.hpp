#ifndef GLSLPROGRAM_HPP
#define GLSLPROGRAM_HPP
#include <GL/glew.h>
#include <string>
#include "Error.hpp"

class GLSLProgram {

public:

    GLSLProgram();
    ~GLSLProgram();

    // Compile Shader from files
    void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    // Compile Shader from in-line source
    void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);

    void linkShaders();
    void addAttribute(const std::string& attributeName);
    GLuint getUniformLocation(const std::string& uniformName);

    void use();
    void unuse();

private:
    void compileShader(const char* source, const std::string& ident, GLuint id);

    int m_numAttributes;
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;

};

#endif //GLSLPROGRAM_HPP
