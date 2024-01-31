#include "utils/debug.hpp"
#include <GLFW/glfw3.h>

#include "hello.h"

void hello() {
    Engine::log("Hello", Engine::LogLevel::INFO);
    Engine::log("Hello", Engine::LogLevel::WARN);
    Engine::log("Hello", Engine::LogLevel::ERROR);
}

void window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    auto wnd = glfwCreateWindow(1280, 720, "Testing", NULL, NULL);

    while (!glfwWindowShouldClose(wnd)) {
        glfwSwapBuffers(wnd);

        glfwPollEvents();
    }
}