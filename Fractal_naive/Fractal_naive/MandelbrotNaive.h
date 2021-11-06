#pragma once
#include "Mandelbrot.h"
#include "Shader.h"
#include "Texture.h"
#include "DrawTool.h"
#include "RGBTable.h"
#include "Vector2.h"

class MandelbrotNaive : public Mandelbrot
{
protected:
    Shader* shader_ = nullptr;
    Texture* texture_ = nullptr;
    DrawTool* drawTool_ = nullptr;
    RGBTable* rgbTable_ = nullptr;

    GLubyte* textureData_ = nullptr;

    int zoomType_ = 0;

    Vector2<size_t> texSize_;
    Vector2<int> fractalSize_;

    double	size_ = 4.0, ratio_ = 0.0;
    Vector2<double> pos_, ltCorner_;

    void generateTextureData();
    void calcZoom(double dt);
    void updatePos();
public:
    MandelbrotNaive(Vector2<int> size);

    virtual void handleMouseClickEvent(int button, int action, int mods);

    virtual void resize(Vector2<int> size);
    virtual void update(double dt);
    virtual void draw();
    virtual void reset();

    ~MandelbrotNaive();
};

