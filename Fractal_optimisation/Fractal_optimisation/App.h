#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <utility>
#include "Mandelbrot.h"
#include "GUI.h"
#include "Vector2.h"

class App {
protected:
    static App* instance_;

    Vector2<int> tmpWinPos_, tmpWinSize_;

    GLFWwindow* window_;
    GLFWmonitor* monitor_;

    GUI* gui_;

    int mouseStatus_ = 0;

    size_t currentFractal_ = 0;
    std::vector<std::pair<std::string, Mandelbrot*>> fractals_;

    App();
public:
    App(App& other) = delete;
    void operator=(const App&) = delete;

    static App* getInstance();

    void toggleFullscreen();
    void loop();

    void setCurrentFractal(size_t index);

    ~App();

    static Vector2<double> getMousePosition();

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
