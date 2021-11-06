#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Color.h"

class Shader
{
protected:
    GLuint id_;

    GLuint loadShader(std::string& shaderCode, const char* name, GLenum shaderType);

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void operator=(const Shader&) = delete;

    void apply();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setColor(const std::string& name, Color color) const;
    void setMat4(const std::string& name, glm::mat4 mat);
};

