#include "Texture.h"
#include "glad/glad.h"

Texture::Texture()
{
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    // powtarzanie koloru tekstury na krawêdziach
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // dok³adna wartoœæ pixela tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

void Texture::updateTexture(GLsizei width, GLsizei height, const GLfloat* pixels)
{
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_FLOAT, pixels);
}

void Texture::apply()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id_);
}

GLuint Texture::getId()
{
    return id_;
}
