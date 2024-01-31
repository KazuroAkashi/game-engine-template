#define GLEW_STATIC
#include "Application.hpp"

#include <GL/glew.h>

#include "platform/GlfwPlatform.hpp"
#include "platform/Platform.hpp"

#include "utils/debug.hpp"

namespace Engine {

Application::Application(Scene* scene, EventBus* eventbus): m_active_scene(scene) {
#if PLATFORM == GLFW
    m_platform = Shared<GlfwPlatform>(new GlfwPlatform(eventbus));
#endif

    scene->m_platform = m_platform;
}

bool Application::start(unsigned int width, unsigned int height, const char* name) const {
    Engine::log("Starting application...");

    bool window_success = m_platform->setup_window(width, height, name);
    if (!window_success) return false;

    Engine::log("Window setup succesful");

    if (glewInit() != GLEW_OK) return false;

    Engine::log("GLEW setup succesful");

    return true;
}

void GLAPIENTRY debugCallback(
    GLenum source [[maybe_unused]],
    GLenum type [[maybe_unused]],
    GLuint id [[maybe_unused]],
    GLenum severity [[maybe_unused]],
    GLsizei length [[maybe_unused]],
    const GLchar* message,
    const void* user_param [[maybe_unused]] ) {

    switch (severity) {
        case GL_DEBUG_SEVERITY_LOW:
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            Engine::log(message, Engine::LogLevel::INFO);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            Engine::log(message, Engine::LogLevel::WARN);
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            Engine::log(message, Engine::LogLevel::ERROR);
            break;
    }


}

void Application::loop() const {
    Engine::log("Starting loop...");

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debugCallback, 0);

    while (!m_platform->window_should_close()) {
        m_active_scene->on_update(1);
        m_active_scene->render();

        m_platform->loop_logic();
    }
}

void Application::destroy() const {
    Engine::log("Cleaning up...");

    m_platform->destroy();
}

Application::~Application() {
    destroy();
}

}  // namespace Engine