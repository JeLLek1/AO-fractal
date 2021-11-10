#include "App.h"
#include "settings.h"
#include "Shader.h"
#include "DrawTool.h"
#include "MandelbrotNaive.h"
#include "MandelbrotOpenCL.h"
#include "MandelbrotShaders.h"
#include "CommandListSelect.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <iostream>

App* App::instance_ = nullptr;

App::App()
{
    fractals_ = {
        std::make_pair("Podejscie naiwne", new MandelbrotNaive()),
        std::make_pair("Optymalizacja przez OpenCL", new MandelbrotOpenCL()),
        std::make_pair("Optymalizacja przez shadery", new MandelbrotShaders()),
    };

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // brak kompatybilnoœci wstecznej
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, nullptr, nullptr);
    if (window_ == nullptr) {
        glfwTerminate();
        std::cout << "ERROR::GLFW: Could not create window" << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, App::framebufferSizeCallback);
    glfwSetMouseButtonCallback(window_, App::mouseButtonCallback);
    glfwSetKeyCallback(window_, App::keyCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // initializacja loadera funckji opengl
    {
        glfwTerminate();
        std::cout << "ERROR::GLAD: Could not load GL" << std::endl;
        exit(EXIT_FAILURE);
    }
    monitor_ = glfwGetPrimaryMonitor();

    glfwGetWindowSize(window_, &tmpWinSize_.x, &tmpWinSize_.y);
    glfwGetWindowPos(window_, &tmpWinPos_.x, &tmpWinPos_.y);

    gui_ = new GUI(Vector2<int>(WINDOW_WIDTH, WINDOW_HEIGHT));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.f, 0.f, 0.f, 1.0f);

    for (auto i : fractals_) {
        i.second->init(Vector2<int>(WINDOW_WIDTH, WINDOW_HEIGHT));
    }
    setCurrentFractal(0);
}

App* App::getInstance()
{
    if (App::instance_ == nullptr) {
        App::instance_ = new App();
    }
    return App::instance_;
}

void App::toggleFullscreen()
{
    if (glfwGetWindowMonitor(window_) == nullptr) {
        glfwGetWindowSize(window_, &tmpWinSize_.x, &tmpWinSize_.y);
        glfwGetWindowPos(window_, &tmpWinPos_.x, &tmpWinPos_.y);

        const GLFWvidmode* mode = glfwGetVideoMode(monitor_);
        glfwSetWindowMonitor(window_, monitor_, 0 , 0, mode->width, mode->height, 0);
    }
    else {
        glfwSetWindowMonitor(window_, nullptr, tmpWinPos_.x, tmpWinPos_.y, tmpWinSize_.x, tmpWinSize_.y, 0);
    }
}

void App::loop()
{
    double lastTime = glfwGetTime();
    double deltaTime = 0.0, nowTime = 0.0;
    while (!glfwWindowShouldClose(window_))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        nowTime = glfwGetTime();
        deltaTime = nowTime - lastTime;
        lastTime = nowTime;


        fractals_[currentFractal_].second->update(deltaTime);
        gui_->update(deltaTime);

        fractals_[currentFractal_].second->draw();
        gui_->draw();

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void App::setCurrentFractal(size_t index)
{
    if (index >= fractals_.size()) return;
    for (auto i : fractals_) {
        i.second->reset();
        i.second->setActive(false);
    }
    fractals_[index].second->setActive(true);
    currentFractal_ = index;

    gui_->setFractalTypeText(fractals_[index].first);
}

App::~App()
{
    for (auto i : fractals_) {
        delete i.second;
    }
    delete gui_;
    glfwDestroyWindow(window_);
    glfwTerminate();
}

Vector2<double> App::getMousePosition()
{
    App* app = App::getInstance();
    Vector2<double> mousePos;
    glfwGetCursorPos(app->window_, &mousePos.x, &mousePos.y);

    return mousePos;
}

void App::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    App* app = App::getInstance();

    for (auto i : app->fractals_) {
        i.second->resize(Vector2<int>(width, height));
    }
    app->gui_->resize(Vector2<int>(width, height));
    
    glViewport(0, 0, width, height);
}

void App::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    App* app = App::getInstance();
    for (auto i : app->fractals_) {
        i.second->handleMouseClickEvent(button, action, mods);
    }
}

void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    App* app = App::getInstance();
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(app->window_, true);
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
        app->toggleFullscreen();
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        app->setCurrentFractal(0);
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        app->setCurrentFractal(1);
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        app->setCurrentFractal(2);
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        app->gui_->startTestTimer();
    }
}
