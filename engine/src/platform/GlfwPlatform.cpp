#if PLATFORM == GLFW
#include "platform/GlfwPlatform.hpp"

#include <GLFW/glfw3.h>

namespace Engine {

bool GlfwPlatform::is_key_down(int keycode) const {
    return glfwGetKey(m_window, keycode) == GLFW_PRESS;
}

void GlfwPlatform::cursor_pos(double* xpos, double* ypos) const {
    glfwGetCursorPos(m_window, xpos, ypos);
}

float GlfwPlatform::get_time() const {
    return glfwGetTime();
}

bool GlfwPlatform::setup_window(unsigned int width, unsigned int height, const char* name) {

    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (!m_window) { return false; }

    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(m_window);

    return true;
}

bool GlfwPlatform::window_should_close() {
    return glfwWindowShouldClose(m_window);
}

void GlfwPlatform::loop_logic() {
    glfwSwapBuffers(m_window);

    glfwPollEvents();
}

void GlfwPlatform::destroy() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

GlfwPlatform::~GlfwPlatform() {
    destroy();
}

}  // namespace Engine

#endif
