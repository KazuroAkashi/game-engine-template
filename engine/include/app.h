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
bool start(unsigned int window_width, unsigned int window_height, const char* window_title);
void loop();
void destroy();
}