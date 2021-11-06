#pragma once
#include <glad/glad.h>
class Texture
{
protected:
    GLuint id_ = 0;

public:
    Texture();
    void operator=(const Texture&) = delete;

    void updateTexture(GLsizei width, GLsizei height, const GLfloat* pixels);
    void apply();

    GLuint getId();
};

