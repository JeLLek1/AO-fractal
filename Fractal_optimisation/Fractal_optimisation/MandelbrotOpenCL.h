#pragma once
#include "Mandelbrot.h"
#include "Shader.h"
#include "Texture.h"
#include "DrawTool.h"
#include "RGBTable.h"
#include "Vector2.h"
#include "OpenCL.h"

class MandelbrotOpenCL : public Mandelbrot
{
protected:
    Shader* shader_ = nullptr;
    Texture* texture_ = nullptr;
    DrawTool* drawTool_ = nullptr;
    RGBTable* rgbTable_ = nullptr;

    std::vector<GLfloat> textureData_;

    Vector2<size_t> texSize_;

    OpenCL* opencl_;

    virtual void updatePos();
    void setupOpenCL();
    void generateTextureData();
public:
    MandelbrotOpenCL();

    virtual void init(Vector2<int> size);

    virtual void resize(Vector2<int> size);
    virtual void update(double dt);
    virtual void draw();

    ~MandelbrotOpenCL();
};

