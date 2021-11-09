#include "MandelbrotNaive.h"
#include "settings.h"
#include "Math.h"
#include "App.h"
#include <glfw/glfw3.h>

MandelbrotNaive::MandelbrotNaive()
{
    
}

void MandelbrotNaive::init(Vector2<int> size)
{
    shader_ = new Shader("shaders/mandelbrot_default/vertex.glsl", "shaders/mandelbrot_default/fragment.glsl");
    texture_ = new Texture();
    drawTool_ = new DrawTool();
    rgbTable_ = new RGBTable(COLORS_COUNT);

    drawTool_->attachShader(shader_);
    drawTool_->attachTexture(texture_);

    drawTool_->pushVertice(Vector2<GLfloat>(1.0f, 1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(1.0f, -1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(-1.0f, -1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(-1.0f, 1.0f));

    drawTool_->pushTIndices(0, 1, 3);
    drawTool_->pushTIndices(1, 2, 3);

    resize(size);
}

void MandelbrotNaive::generateTextureData()
{
    if (fractalSize_.x * fractalSize_.y <= 0) return;
    for (size_t y = 0; y < fractalSize_.y; y++) {
        double c_im = ratio_ * y + ltCorner_.y;
        for (size_t x = 0; x < fractalSize_.x; x++) {
            double c_re = ratio_ * x + ltCorner_.x;

            size_t level = 0;
            double z_re = 0, z_im = 0, tmp_re;

            do {
                tmp_re = z_re * z_re - z_im * z_im + c_re;
                z_im = c_im + 2 * z_re * z_im;
                z_re = tmp_re;

                level++;
            } while (z_re * z_re + z_im * z_im < 4 && level < MAX_LEVELS);

            size_t pos = (y * texSize_.x + x) * 3;
            if (level == MAX_LEVELS) {
                textureData_[pos] = textureData_[pos + 1] = textureData_[pos + 2] = 0;
            } else {
                textureData_[pos] = rgbTable_->getRub(level);
                textureData_[pos + 1] = rgbTable_->getGub(level);
                textureData_[pos + 2] = rgbTable_->getBub(level);
            }
        }
    }
}

void MandelbrotNaive::resize(Vector2<int> size)
{
    texSize_ = Vector2<size_t>(Math::get_pow_2(static_cast<size_t>(size.x)), Math::get_pow_2(size.y));
    fractalSize_ = size;
    Vector2<GLfloat> texCut = Vector2<GLfloat>(
        static_cast<GLfloat>(fractalSize_.x) / texSize_.x,
        static_cast<GLfloat>(fractalSize_.y) / texSize_.y
        );

    drawTool_->clearUVs();
    drawTool_->pushUV(Vector2<GLfloat>(texCut.x, texCut.y));
    drawTool_->pushUV(Vector2<GLfloat>(texCut.x, 0.0f));
    drawTool_->pushUV(Vector2<GLfloat>(0.0f, 0.0f));
    drawTool_->pushUV(Vector2<GLfloat>(0.0f, texCut.y));
    drawTool_->commit();
    
    textureData_.resize(texSize_.x * texSize_.y * 3);

    updatePos();
}

void MandelbrotNaive::update(double dt)
{
    calcZoom(dt);
    if (!active_) return;
    generateTextureData();
    texture_->updateTexture(static_cast<GLsizei>(texSize_.x), static_cast<GLsizei>(texSize_.y), textureData_.data());
}

void MandelbrotNaive::draw()
{
    drawTool_->draw();
}

MandelbrotNaive::~MandelbrotNaive()
{
    delete shader_;
    delete texture_;
    delete drawTool_;
    delete rgbTable_;
}
