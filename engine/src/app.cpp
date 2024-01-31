#include "utils/debug.hpp"
#include <GL/glew.h>

#include "app.hpp"

namespace Engine {

bool start(const StartOptions options) {
    bool window_success = Engine::platform->setup_window(options.window_width, options.window_height, options.window_title);
    if (!window_success) return false;

    if (glewInit() != GLEW_OK) return false;

    return true;
}

void loop() {
    while (!platform->window_should_close()) {
        platform->loop_logic();
    }
}

void destroy() {
    platform->destroy();
}

}