#include "MandelbrotOpenCL.h"
#include "settings.h"
#include "Math.h"
#include "App.h"
#include "CommandListSelect.h"
#include <glfw/glfw3.h>
#include <iostream>

MandelbrotOpenCL::MandelbrotOpenCL()
{
    setupOpenCL();
}

void MandelbrotOpenCL::setupOpenCL()
{
    opencl_ = new OpenCL();
    std::vector<std::string> availablePlatforms = opencl_->getAvailablePlatforms();
    CommandListSelect platformSelect("(OpenCL) Wybierz platforme:", availablePlatforms);
    if (!opencl_->applyPlatform(platformSelect.run())) {
        std::cout << "ERROR::OPEN_CL: Could not select platform" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> availableDevices = opencl_->getAvailableDevices();
    CommandListSelect deviceSelect("(OpenCL) Wybierz urzadzenie:", availableDevices);
    if (!opencl_->applyDevide(deviceSelect.run())) {
        std::cout << "ERROR::OPEN_CL: Could not select device" << std::endl;
        exit(EXIT_FAILURE);
    }
    opencl_->init(
        "opencl/mandelbrot.cl",
        "get_color", {
            "fractalSize",
            "ltCorner",
            "texSize",
            "maxLevels",
            "ratio",
            "maxColors",
            "colorTable",
            "texture"
        });
}

void MandelbrotOpenCL::updatePos()
{
    Mandelbrot::updatePos();
    opencl_->enqueueData("fractalSize", fractalSize_);
    opencl_->enqueueData("ltCorner", ltCorner_);
    opencl_->enqueueData("texSize", texSize_);
    opencl_->enqueueData("ratio", ratio_);
}

void MandelbrotOpenCL::init(Vector2<int> size)
{
    shader_ = new Shader("shaders/mandelbrot_default/vertex.glsl", "shaders/mandelbrot_default/fragment.glsl");
    texture_ = new Texture();
    drawTool_ = new DrawTool();
    rgbTable_ = new RGBTable(COLORS_COUNT);
    opencl_->enqueueData("maxLevels", MAX_LEVELS);
    opencl_->enqueueData("maxColors", COLORS_COUNT);
    opencl_->enqueueVectorData("colorTable", rgbTable_->getColorsVectorub()); 

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

void MandelbrotOpenCL::generateTextureData()
{
    if (fractalSize_.x * fractalSize_.y <= 0) return;
    opencl_->run(static_cast<size_t>(fractalSize_.x) * static_cast<size_t>(fractalSize_.y));
    opencl_->readVectorResult("texture", textureData_);
}

void MandelbrotOpenCL::resize(Vector2<int> size)
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

    opencl_->enqueueReadVector("texture", textureData_);

    updatePos();
}

void MandelbrotOpenCL::update(double dt)
{
    calcZoom(dt);
    if (!active_) return;
    generateTextureData();
    texture_->updateTexture(static_cast<GLsizei>(texSize_.x), static_cast<GLsizei>(texSize_.y), textureData_.data());
}

void MandelbrotOpenCL::draw()
{
    drawTool_->draw();
}

MandelbrotOpenCL::~MandelbrotOpenCL()
{
    delete shader_;
    delete texture_;
    delete drawTool_;
    delete rgbTable_;
    delete opencl_;
}
