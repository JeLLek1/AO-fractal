#include "Shader.h"
#include "FileLoader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

GLuint Shader::loadShader(std::string& shaderCode, const char* name, GLenum shaderType)
{
    GLuint id;
    GLint success;
    GLchar infoLog[512];
    const char* cShaderCode = shaderCode.c_str();

    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &cShaderCode, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::" << name << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    };

    return id;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    GLint success;
    GLchar infoLog[512];

    FileLoader vertexLoader(vertexPath);
    FileLoader fragmentLoader(fragmentPath);
    std::string vertexCode = vertexLoader.load();
    std::string fragmentCode = fragmentLoader.load();

    id_ = glCreateProgram();
    unsigned int vertex = loadShader(vertexCode, "VERTEX", GL_VERTEX_SHADER);
    unsigned int fragment = loadShader(fragmentCode, "FRAGMENT", GL_FRAGMENT_SHADER);
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);

    glGetProgramiv(id_, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::apply()
{
    glUseProgram(id_);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUseProgram(id_);
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUseProgram(id_);
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setuInt(const std::string& name, unsigned int value) const
{
    glUseProgram(id_);
    glUniform1ui(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUseProgram(id_);
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setColor(const std::string& name, Color color) const
{
    glUseProgram(id_);
    glUniform4f(glGetUniformLocation(id_, name.c_str()), color.r, color.g, color.b, color.a);
}

void Shader::setDouble(const std::string& name, double value) const
{
    glUseProgram(id_);
    glUniform1d(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setVec2d(const std::string& name, Vector2<double> value) const
{
    glUseProgram(id_);
    glUniform2d(glGetUniformLocation(id_, name.c_str()), value.x, value.y);
}

void Shader::setVec2f(const std::string& name, Vector2<float> value) const
{
    glUseProgram(id_);
    glUniform2f(glGetUniformLocation(id_, name.c_str()), value.x, value.y);
}

void Shader::setVec2i(const std::string& name, Vector2<int> value) const
{
    glUseProgram(id_);
    glUniform2i(glGetUniformLocation(id_, name.c_str()), value.x, value.y);
}

void Shader::setMat4(const std::string& name, glm::mat4 mat)
{
    glUseProgram(id_);
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
