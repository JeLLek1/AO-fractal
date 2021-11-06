#pragma once
#include "Mandelbrot.h"

class MandelbrotShaders : public Mandelbrot
{
public:
    MandelbrotShaders();

    virtual void init(Vector2<int> size);

    virtual void resize(Vector2<int> size);
    virtual void update(double dt);
    virtual void draw();
};

