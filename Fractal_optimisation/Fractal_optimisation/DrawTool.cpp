#include "DrawTool.h"
#include <glad/glad.h>
#include <vector>

DrawTool::DrawTool()
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
}

void DrawTool::pushVertice(Vector2<GLfloat> vertice)
{
    vertices_.push_back(vertice);
}

void DrawTool::pushUV(Vector2<GLfloat> uv)
{
    UVs_.push_back(uv);
}

void DrawTool::pushColor(Color color)
{
    colors_.push_back(color);
}

void DrawTool::pushTIndices(GLint a, GLint b, GLint c)
{
    indices_.push_back(a);
    indices_.push_back(b);
    indices_.push_back(c);
}

void DrawTool::clearVertices()
{
    vertices_.clear();
}

void DrawTool::clearUVs()
{
    UVs_.clear();
}

void DrawTool::clearColors()
{
    colors_.clear();
}

void DrawTool::clearIndices()
{
    indices_.clear();
}

void DrawTool::attachShader(Shader* shader)
{
    shader_ = shader;
}

void DrawTool::attachTexture(Texture* texture)
{
    texture_ = texture;
}

void DrawTool::commit()
{
    indicesCount_ = indices_.size();
    size_t vIndex;
    std::vector<GLint> vIndices{ indices_.begin(), indices_.end() };
    std::vector<GLfloat> vVertices(vertices_.size() * vectorSize, 0.0);

    // v.x, v.y, v.z, c.r, c.g, c.b, c.a, uv.s, uv.t 
    vIndex = 0;
    for (auto it = vertices_.begin(); it != vertices_.end(); ++it) {
        vVertices[vIndex] = it->x;
        vVertices[vIndex + 1] = it->y;
        vVertices[vIndex + 2] = 0.0f;
        vIndex += vectorSize;
    }

    vIndex = 0;
    for (auto it = colors_.begin(); it != colors_.end(); ++it) {
        if (vIndex + 9 > vVertices.size()) {
            break;
        }
        vVertices[vIndex + 3] = it->r;
        vVertices[vIndex + 4] = it->g;
        vVertices[vIndex + 5] = it->b;
        vVertices[vIndex + 6] = it->a;
        vIndex += vectorSize;
    }

    vIndex = 0;
    for (auto it = UVs_.begin(); it != UVs_.end(); ++it) {
        if (vIndex + 9 > vVertices.size()) {
            break;
        }
        vVertices[vIndex + 7] = it->x;
        vVertices[vIndex + 8] = it->y;
        vIndex += vectorSize;
    }

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(GLfloat), &vVertices.front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vIndices.size() * sizeof(GLint), &vIndices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(vectorSize * sizeof(GLfloat)), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(vectorSize * sizeof(GLfloat)), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(vectorSize * sizeof(GLfloat)), (void*)(7 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    if (shader_ != nullptr && texture_ != nullptr) {
        shader_->apply();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void DrawTool::draw()
{
    if (texture_ != nullptr) {
        texture_->apply();
    }
    if (shader_ != nullptr) {
        shader_->apply();
    }
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indicesCount_), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

DrawTool::~DrawTool()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
    glDeleteBuffers(1, &EBO_);
}
