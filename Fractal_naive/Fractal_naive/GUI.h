#pragma once
#include "Font.h"
#include "Text.h"
#include "Shader.h"
class GUI
{
protected:
    Shader* shader_;
    Font* font_;
    Text* fractalTypeText_;
    Text* fpsCounterText_;

    double frameCountTime_ = 0.0;
    unsigned long frameCount_ = 0;

    void setFPSText(double fps);
public:
    GUI(Vector2<int> size);
    void operator=(const GUI&) = delete;

    void setFractalTypeText(std::string text);

    void resize(Vector2<int> size);
    void update(double dt);
    void draw();

    ~GUI();
};

