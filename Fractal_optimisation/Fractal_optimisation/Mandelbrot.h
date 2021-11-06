#pragma once
#include "Vector2.h"

class Mandelbrot
{
protected:
    bool active_ = false;

    int zoomType_ = 0;

    double	size_ = 4.0, ratio_ = 0.0;
    Vector2<double> pos_, ltCorner_;
    Vector2<int> fractalSize_;

    virtual void updatePos();
    void calcZoom(double dt);
public:
    virtual void handleMouseClickEvent(int button, int action, int mods);
    void operator=(const Mandelbrot&) = delete;

    virtual void setActive(bool active);

    virtual void init(Vector2<int> size) = 0;

    virtual void resize(Vector2<int> size) = 0;
    virtual void update(double dt) = 0;
    virtual void draw() = 0;
    virtual void reset();
};

