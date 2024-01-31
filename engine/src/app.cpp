#include "utils/debug.hpp"
#include <GL/glew.h>

#include "app.h"

namespace Engine {

bool start(unsigned int window_width, unsigned int window_height, const char* window_title) {
    bool window_success = Engine::platform->setup_window(window_width, window_height, window_title);
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