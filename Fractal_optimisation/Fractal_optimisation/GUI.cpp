#include <string>
#include "GUI.h"
#include "settings.h"

GUI::GUI(Vector2<int> size)
{
    shader_ = new Shader("shaders/text/vertex.glsl", "shaders/text/fragment.glsl");
    font_ = new Font("assets/fonts/roboto.ttf", 30);
    testMsPerFrameText_ = new Text(font_);
    testMsPerFrameText_->attachShader(shader_);
    testMsPerFrameText_->setScale(1.0);
    testMsPerFrameText_->setColor(Color(1.f, 1.f, 1.f, 1.f));
    testMsPerFrameText_->setPosition(Vector2<GLfloat>(10.0, 90.0f));
    fractalTypeText_ = new Text(font_);
    fractalTypeText_->attachShader(shader_);
    fractalTypeText_->setScale(1.0);
    fractalTypeText_->setColor(Color(1.f, 1.f, 1.f, 1.f));
    fractalTypeText_->setPosition(Vector2<GLfloat>(10.0f, 50.0f));
    fpsCounterText_ = new Text(font_);
    fpsCounterText_->attachShader(shader_);
    fpsCounterText_->setScale(1.0);
    fpsCounterText_->setColor(Color(1.f, 1.f, 1.f, 1.f));
    fpsCounterText_->setPosition(Vector2<GLfloat>(10.0, 10.0f));
    setFPSText(-1.0);
    setTestMsPerFrameText();
    setFractalTypeText("-");

    resize(size);
}

void GUI::setFPSText(double fps)
{
    std::string fpsText = "-";
    if (fps > 0.0) {
        fpsText = std::to_string(fps);
    }
    fpsCounterText_->setText("Klatek na sekunde: " + fpsText);
}

void GUI::setTestMsPerFrameText(TestState testState, double time)
{
    if (testState != TestState::HOLD) {
        testState_ = testState;
    }
    switch (testState_) {
    case TestState::WAIT:
        testMsPerFrameText_->setText(
            "Nacisnij spacje aby rozpoczac");
        break;
    case TestState::MEASURE:
        testMsPerFrameText_->setText(
            "Trwa wykonywanie pomiaru ( "
            + std::to_string(frameCountTest_)
            + "/"
            + std::to_string(TEST_AFTER_FRAMES)
            + " )");
        break;
    case TestState::DISPLAY:
        testMsPerFrameText_->setText("Czas generowania klatki: " + std::to_string(time) + " s");
        break;
    }
}

void GUI::setFractalTypeText(std::string text)
{
    setTestMsPerFrameText(TestState::WAIT);
    fractalTypeText_->setText("Typ implementacji: " + text);
}

void GUI::startTestTimer()
{
    frameCountTimeTest_ = 0.0;
    frameCountTest_ = 0;
    setTestMsPerFrameText(TestState::MEASURE);
}

void GUI::resize(Vector2<int> size)
{
    fractalTypeText_->setProjectionMatrix(size);
    fpsCounterText_->setProjectionMatrix(size);
}

void GUI::update(double dt)
{
    frameCount_++;
    frameCountTime_ += dt;
    if (frameCountTime_ >= REFRESH_FPS_MIN_TIME) {
        setFPSText(frameCount_ / frameCountTime_);
        frameCount_ = 0;
        frameCountTime_ = 0.0;
    }
    if (testState_ != TestState::DISPLAY && testState_ != TestState::WAIT) {
        if (frameCountTest_ < TEST_AFTER_FRAMES) {
            frameCountTest_++;
            frameCountTimeTest_ += dt;
            setTestMsPerFrameText();
        }
        else if (frameCountTest_ == TEST_AFTER_FRAMES) {
            setTestMsPerFrameText(TestState::DISPLAY, frameCountTimeTest_ / frameCountTest_);
            frameCountTest_++;
        }
    }
}

void GUI::draw()
{
    fractalTypeText_->draw();
    fpsCounterText_->draw();
    testMsPerFrameText_->draw();
}

GUI::~GUI()
{
    delete fractalTypeText_;
    delete fpsCounterText_;
    delete testMsPerFrameText_;
    delete font_;
    delete shader_;
}
