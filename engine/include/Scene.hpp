#pragma once

#include "ext/entt.hpp"
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"

namespace Engine {

class Scene final {
private:
    entt::registry m_registry;
    class Camera* m_camera = nullptr;
    Shared<const Platform> m_platform;
    Renderer m_renderer;

    friend class Entity;
    friend class Application;

    template <typename T, typename... Args>
    inline auto& add_component(entt::entity entity_id, Args&&... args) {
        return m_registry.emplace<T, Args...>(entity_id, std::forward<Args>(args)...);
    }

    template <typename... Component>
    inline auto& get_component(entt::entity entity_id) {
        // This had to be done here because of "auto deduction" rules
        return m_registry.get<Component...>(entity_id);
    }

public:
    Scene(): m_renderer(Renderer(this)) {}
    ~Scene();

    void prepare();

    void set_camera(class Camera* camera);
    class Camera* camera() const;

    entt::entity new_entity();

    template <typename Component, typename... Other, typename... Exclude>
    auto entity_view(entt::exclude_t<Exclude...> exclude = {}) const {
        // This had to be done here because of "auto deduction" rules
        return m_registry.view<Component, Other..., Exclude...>(exclude);
    }

    void destroy_entity(entt::entity entity_id);

    void on_update(float delta);
    void render();

    void attach_shader(const Shader& shader) const;
};

}  // namespace Engine
