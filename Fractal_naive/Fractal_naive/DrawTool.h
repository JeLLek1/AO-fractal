#pragma once
#include <list>
#include "Shader.h"
#include "Texture.h"
#include "Vector2.h"
#include "Color.h"

class DrawTool
{
protected:
    const size_t vectorSize = 9;

    GLuint VBO_; // buffor wierzcho³ków obiektu
    GLuint VAO_; // buffor tablicy wierzcho³ków
    GLuint EBO_; // buffor elementów obiektu

    std::list <Vector2<GLfloat>> vertices_;
    std::list <Color> colors_;
    std::list <Vector2<GLfloat>> UVs_;
    std::list <GLint> indices_;

    size_t indicesCount_ = 0;

    Texture* texture_ = nullptr;
    Shader* shader_ = nullptr;
public:
    DrawTool();
    void operator=(const DrawTool&) = delete;

    void pushVertice(Vector2<GLfloat> vertice);
    void pushUV(Vector2<GLfloat> uv);
    void pushColor(Color color);
    void pushTIndices(GLint a, GLint b, GLint c);
    void clearVertices();
    void clearUVs();
    void clearColors();
    void clearIndices();
    void attachShader(Shader* shader);
    void attachTexture(Texture* texture);
    void commit();

    void draw();

    ~DrawTool();
};

