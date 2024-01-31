#pragma once

#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

#if PLATFORM == GLFW
#include "platform/GlfwPlatform.hpp"

namespace Engine {
const auto platform = Ref<GlfwPlatform>(new GlfwPlatform());
}
#endif

namespace Engine {

struct StartOptions {
    unsigned int window_width;
    unsigned int window_height;
    const char* window_title;

    unsigned int batch_max_quads;
};

bool start(const StartOptions options);
void loop();
void destroy();
}