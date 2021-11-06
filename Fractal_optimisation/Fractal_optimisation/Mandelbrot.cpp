#include "Mandelbrot.h"
#include "App.h"
#include <glfw/glfw3.h>

void Mandelbrot::updatePos()
{
    if (fractalSize_.y > fractalSize_.x) {
        ratio_ = size_ / fractalSize_.x;

        ltCorner_.x = pos_.x - size_ * 0.5;
        ltCorner_.y = pos_.y - (size_ * fractalSize_.y / fractalSize_.x) * 0.5;
    }
    else {
        ratio_ = size_ / fractalSize_.y;
        ltCorner_.y = pos_.y - size_ * 0.5;
        ltCorner_.x = pos_.x - (size_ * fractalSize_.x / fractalSize_.y) * 0.5;
    }
}

void Mandelbrot::calcZoom(double dt)
{
    if (zoomType_ == 0) return;
    Vector2<double> mousePos = App::getMousePosition();
    double sizeChange = dt * zoomType_ * size_;
    size_ += sizeChange;

    if (fractalSize_.y > fractalSize_.x) {
        pos_.x += (0.5 - (static_cast<double>(mousePos.x) / fractalSize_.x)) * sizeChange * fractalSize_.y / fractalSize_.x;
    }
    else {
        pos_.x += (0.5 - (static_cast<double>(mousePos.x) / fractalSize_.x)) * sizeChange * fractalSize_.x / fractalSize_.y;
    }
    pos_.y -= (0.5 - (static_cast<double>(mousePos.y) / fractalSize_.y)) * sizeChange;

    updatePos();
}

void Mandelbrot::handleMouseClickEvent(int button, int action, int mods)
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

void Mandelbrot::setActive(bool active)
{
    active_ = active;
}

void Mandelbrot::reset()
{
    pos_ = Vector2<double>(0.0, 0.0);
    size_ = 4.0;

    updatePos();
}
