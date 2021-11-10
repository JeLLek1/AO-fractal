#pragma once
#include "Font.h"
#include "Text.h"
#include "Shader.h"
enum class TestState: char {
    HOLD = 0,
    WAIT = 1,
    MEASURE = 2,
    DISPLAY = 3,
};
class GUI
{
protected:
    Shader* shader_;
    Font* font_;
    Text* fractalTypeText_;
    Text* fpsCounterText_;
    Text* testMsPerFrameText_;

    double frameCountTime_ = 0.0;
    unsigned long frameCount_ = 0;

    double frameCountTimeTest_ = 0.0;
    unsigned long frameCountTest_ = 0;
    TestState testState_ = TestState::WAIT;

    void setFPSText(double fps);
    void setTestMsPerFrameText(TestState testState = TestState::HOLD, double time = 0.0);
public:
    GUI(Vector2<int> size);
    void operator=(const GUI&) = delete;

    void setFractalTypeText(std::string text);

    void startTestTimer();

    void resize(Vector2<int> size);
    void update(double dt);
    void draw();

    ~GUI();
};

