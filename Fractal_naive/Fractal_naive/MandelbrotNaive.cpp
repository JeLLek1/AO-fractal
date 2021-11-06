#include "MandelbrotNaive.h"
#include "settings.h"
#include "Math.h"
#include "App.h"
#include <glfw/glfw3.h>

MandelbrotNaive::MandelbrotNaive(Vector2<int> size)
{
    shader_ = new Shader("shaders/mandelbrot_naive/vertex.glsl", "shaders/mandelbrot_naive/fragment.glsl");
    texture_ = new Texture();
    drawTool_ = new DrawTool();
    rgbTable_ = new RGBTable(COLORS_COUNT);

    drawTool_->attachShader(shader_);
    drawTool_->attachTexture(texture_);

    drawTool_->pushVertice(Vector2<GLfloat>(1.0f, 1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(1.0f, -1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(-1.0f, -1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(-1.0f, 1.0f));

    drawTool_->pushUV(Vector2<GLfloat>(1.0f, 1.0f));
    drawTool_->pushUV(Vector2<GLfloat>(1.0f, 0.0f));
    drawTool_->pushUV(Vector2<GLfloat>(0.0f, 0.0f));
    drawTool_->pushUV(Vector2<GLfloat>(0.0f, 1.0f));

    drawTool_->pushTIndices(0, 1, 3);
    drawTool_->pushTIndices(1, 2, 3);

    drawTool_->commit();

    resize(size);
}

void MandelbrotNaive::handleMouseClickEvent(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS && zoomType_ == 0) {
            zoomType_ = -1;
        }
        else if (zoomType_ == -1) {
            zoomType_ = 0;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS && zoomType_ == 0) {
            zoomType_ = 1;
        }
        else if (zoomType_ == 1) {
            zoomType_ = 0;
        }
    }
}

void MandelbrotNaive::generateTextureData()
{
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

void MandelbrotNaive::updatePos()
{
    if (fractalSize_.y > fractalSize_.x) {
        ratio_ = size_ / fractalSize_.x;

        ltCorner_.x = pos_.x - size_ * 0.5;
        ltCorner_.y = pos_.y - (size_ * fractalSize_.y / fractalSize_.x) * 0.5;
    } else {
        ratio_ = size_ / fractalSize_.y;
        ltCorner_.y = pos_.y - size_ * 0.5;
        ltCorner_.x = pos_.x - (size_ * fractalSize_.x / fractalSize_.y) * 0.5;
    }
}

void MandelbrotNaive::calcZoom(double dt)
{
    if (zoomType_ == 0) return;
    Vector2<double> mousePos = App::getMousePosition();
    double sizeChange = dt * zoomType_ * size_;
    size_ += sizeChange;

    if (fractalSize_.y > fractalSize_.x) {
        pos_.x += (0.5 - (static_cast<double>(mousePos.x) / fractalSize_.x)) * sizeChange * fractalSize_.y / fractalSize_.x;
    } else {
        pos_.x += (0.5 - (static_cast<double>(mousePos.x) / fractalSize_.x)) * sizeChange * fractalSize_.x / fractalSize_.y;
    }
    pos_.y -= (0.5 - (static_cast<double>(mousePos.y) / fractalSize_.y)) * sizeChange;

    updatePos();
}

void MandelbrotNaive::resize(Vector2<int> size)
{
    if (textureData_ != nullptr) {
        delete[] textureData_;
    }
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
    
    textureData_ = new GLubyte[texSize_.x * texSize_.y * 3];

    updatePos();
}

void MandelbrotNaive::update(double dt)
{
    calcZoom(dt);
    if (!active_) return;
    generateTextureData();
    texture_->updateTexture(static_cast<GLsizei>(texSize_.x), static_cast<GLsizei>(texSize_.y), textureData_);
}

void MandelbrotNaive::draw()
{
    drawTool_->draw();
}

void MandelbrotNaive::reset()
{
    pos_ = Vector2<double>(0.0, 0.0);
    size_ = 4.0;

    updatePos();
}

MandelbrotNaive::~MandelbrotNaive()
{
    delete shader_;
    delete texture_;
    delete drawTool_;
    delete rgbTable_;
    delete[] textureData_;
}
