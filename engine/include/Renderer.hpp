#pragma once

#include <unordered_map>

#include "Shader.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"

namespace Engine {

class Renderer final {
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ibo;
    unsigned int m_program;
    unsigned int m_batch_max_quads = 10000;

    const class Scene* m_scene;

    std::unordered_map<std::string, int> m_uniform_cache;
    int get_uniform_location(const char* name);
    void render();

    friend class Application;
    friend class Scene;

public:
    Renderer(const Scene* const scene)
        : m_scene(scene) {}
    ~Renderer();
    bool setup();
    void attach_shader(const Shader& shader) const;
};
}  // namespace Engine