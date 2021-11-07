#pragma once
#include "Mandelbrot.h"
#include "Shader.h"
#include "DrawTool.h"
#include "RGBTable.h"
#include "Vector2.h"

class MandelbrotShaders : public Mandelbrot
{
protected:

    Shader* shader_ = nullptr;
    DrawTool* drawTool_ = nullptr;
    RGBTable* rgbTable_ = nullptr;

    GLuint SSBO_ = 0;

    virtual void updatePos();
public:
    MandelbrotShaders();

    virtual void init(Vector2<int> size);

    virtual void resize(Vector2<int> size);
    virtual void update(double dt);
    virtual void draw();

    ~MandelbrotShaders();
};

