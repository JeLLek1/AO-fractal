#include "MandelbrotShaders.h"

void MandelbrotShaders::updatePos()
{
    Mandelbrot::updatePos();
    shader_->setVec2d("ltCorner", ltCorner_);
    shader_->setDouble("ratio", ratio_);
}

MandelbrotShaders::MandelbrotShaders()
{
}

void MandelbrotShaders::init(Vector2<int> size)
{
    shader_ = new Shader("shaders/mandelbrot_opt_shader/vertex.glsl", "shaders/mandelbrot_opt_shader/fragment.glsl");
    drawTool_ = new DrawTool();
    rgbTable_ = new RGBTable(COLORS_COUNT);

    shader_->setuInt("maxColors", COLORS_COUNT);
    shader_->setuInt("maxLevels", MAX_LEVELS);

    drawTool_->attachShader(shader_);

    drawTool_->pushVertice(Vector2<GLfloat>(1.0f, 1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(1.0f, -1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(-1.0f, -1.0f));
    drawTool_->pushVertice(Vector2<GLfloat>(-1.0f, 1.0f));

    drawTool_->pushColor({ 1.0, 1.0, 1.0, 1.0 });
    drawTool_->pushColor({ 1.0, 0.0, 1.0, 1.0 });
    drawTool_->pushColor({ 1.0, 1.0, 0.0, 1.0 });
    drawTool_->pushColor({ 1.0, 0.0, 0.0, 1.0 });

    drawTool_->pushTIndices(0, 1, 3);
    drawTool_->pushTIndices(1, 2, 3);

    drawTool_->commit();

    glGenBuffers(1, &SSBO_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_);
    glBufferData(GL_SHADER_STORAGE_BUFFER, rgbTable_->getColorsVectorSize(), rgbTable_->getColorsVector().data(), GL_STATIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO_);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    resize(size);
}

void MandelbrotShaders::resize(Vector2<int> size)
{
    fractalSize_ = size;
    updatePos();
}

void MandelbrotShaders::update(double dt)
{
    calcZoom(dt);
    if (!active_) return;
}

void MandelbrotShaders::draw()
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO_);
    drawTool_->draw();
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

MandelbrotShaders::~MandelbrotShaders()
{
    delete shader_;
    delete drawTool_;
    delete rgbTable_;
}
