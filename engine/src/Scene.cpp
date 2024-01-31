#include "Scene.hpp"

#include "Camera.hpp"
#include "entity/ScriptComponent.hpp"

#include "utils/debug.hpp"

namespace Engine {

void Scene::prepare() {
    Engine::log("Preparing scene...");

    auto view = entity_view<ScriptComponent>();

    for (auto [entity, script_comp] : view.each()) {
        ScriptComponent& mut_script_comp = const_cast<ScriptComponent&>(script_comp);
        mut_script_comp.m_game_script = Ref<GameScript>(script_comp.init_script());

        mut_script_comp.m_game_script->m_entity = script_comp.m_entity;
        mut_script_comp.m_game_script->m_platform = m_platform;

        script_comp.m_game_script->on_create();
    }

    m_renderer.setup();
}

Scene::~Scene() {
    Engine::log("Destroying scene...");

    auto view = entity_view<ScriptComponent>();

    for (auto [entity, script_comp] : view.each()) { script_comp.m_game_script->on_destroy(); }
}

void Scene::set_camera(Camera* camera) {
    m_camera = camera;
}

Camera* Scene::camera() const {
    if (!m_camera) {
        Engine::log("Camera not set for the scene", Engine::LogLevel::ERROR);
    }
    return m_camera;
}

entt::entity Scene::new_entity() {
    Engine::log("Creating new entity...");
    return m_registry.create();
}

void Scene::destroy_entity(entt::entity entity_id) {
    Engine::log("Destroying entity...");
    m_registry.destroy(entity_id);
}

void Scene::on_update(float delta) {
    auto view = entity_view<ScriptComponent>();

    for (auto [entity, script_comp] : view.each()) { script_comp.m_game_script->on_update(delta); }
}

void Scene::render() {
    m_renderer.render();
}

void Scene::attach_shader(const Shader& shader) const {
    m_renderer.attach_shader(shader);
}

}  // namespace Engine