#pragma once
#include "Vector2.h"

class Mandelbrot
{
protected:
    bool active_ = false;
public:
    virtual void handleMouseClickEvent(int button, int action, int mods) = 0;
    void operator=(const Mandelbrot&) = delete;

    virtual void setActive(bool active);

    virtual void resize(Vector2<int> size) = 0;
    virtual void update(double dt) = 0;
    virtual void draw() = 0;
    virtual void reset() = 0;
};

