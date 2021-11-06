#pragma once
#include <glad/glad.h>
#include <string>
#include "Font.h"
#include "Shader.h"
#include "Vector2.h"
#include "Color.h"

class Text
{
protected:
    Font* font_;

    GLuint VBO_; // buffor wierzcho³ków obiektu
    GLuint VAO_; // buffor tablicy wierzcho³ków

    std::string text_;
    Vector2<GLfloat> position_;
    Color color_;
    GLfloat scale_ = 1.f;


    Shader* shader_ = nullptr;
public:
    Text(Font* font);
    void operator=(const Text&) = delete;

    void attachShader(Shader* shader);
    void setText(std::string text);
    void setColor(Color color);
    void setScale(GLfloat scale);
    void setPosition(Vector2<GLfloat> position);
    void setProjectionMatrix(Vector2<int> size);

    void draw();

    ~Text();
};

