#pragma once
#include "platform/Platform.hpp"
#include "utils/Memory.hpp"
#include "Scene.hpp"

namespace Engine {

class Application final {
private:
    Shared<Platform> m_platform;
    Scene* m_active_scene;

public:
    Application(Scene* scene, EventBus* eventbus);
    ~Application();

    void set_active_scene(Scene* scene) {
        m_active_scene = scene;
    }

    Scene* get_active_scene() const {
        return m_active_scene;
    }

    bool start(unsigned int width, unsigned int height, const char* name) const;
    void loop() const;
    void destroy() const;
};

}  // namespace Engine