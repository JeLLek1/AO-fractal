#include "Text.h"
#include <glm/gtc/matrix_transform.hpp>

Text::Text(Font* font)
{
    font_ = font;
    glGenVertexArrays(1, &VBO_);
    glGenBuffers(1, &VAO_);
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

// wywo³aæ przez przypisaniem koloru i macierzy projekcji
void Text::attachShader(Shader* shader)
{
    shader_ = shader;
}

void Text::setText(std::string text)
{
    text_ = text;
}

void Text::setColor(Color color)
{
    color_ = color;
    if (shader_ != nullptr) {
        shader_->setColor("textColor", color_);
    }
}

void Text::setScale(GLfloat scale)
{
    scale_ = scale;
}

void Text::setPosition(Vector2<GLfloat> position)
{
    position_ = position;
}

void Text::setProjectionMatrix(Vector2<int> size)
{
    if (shader_ != nullptr) {
        shader_->setMat4("projection", glm::ortho(0.0f, static_cast<GLfloat>(size.x), 0.0f, static_cast<GLfloat>(size.y)));
    }
}

void Text::draw()
{
    if (shader_ != nullptr) {
        shader_->apply();
    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO_);

    GLfloat shiftX = 0;

    for (auto c = text_.begin(); c != text_.end(); c++)
    {
        Character ch = font_->getCharacter(*c);

        Vector2<GLfloat> pos = Vector2<GLfloat>(
            position_.x + ch.bearing.x * scale_ + shiftX,
            position_.y - (ch.size.y - ch.bearing.y) * scale_);

        Vector2<GLfloat> size = Vector2<GLfloat>(ch.size.x * scale_, ch.size.y * scale_);

        float vertices[6][4] = {
            { pos.x,            pos.y + size.y, 0.0f, 0.0f },
            { pos.x,            pos.y,          0.0f, 1.0f },
            { pos.x + size.x,   pos.y,          1.0f, 1.0f },
            { pos.x,            pos.y + size.y, 0.0f, 0.0f },
            { pos.x + size.x,   pos.y,          1.0f, 1.0f },
            { pos.x + size.x,   pos.y + size.y, 1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6); 
        shiftX += (ch.advance >> 6) * scale_; // 2^64 - 1/64 to iloœæ pixeli
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Text::~Text()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}
