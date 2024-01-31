#pragma once

#include "Camera.hpp"
#include "entity/GameScript.hpp"
#include "entity/TransformComponent.hpp"
#include "glm/glm.hpp"
#include "input/Keys.hpp"

namespace Engine {

class FirstPersonWalkingCamera: public GameScript {
private:
    Camera* m_camera;
    double m_lastx = 0;
    double m_lasty = 0;
    bool first = true;

protected:
    virtual void on_create() override {
        m_camera = static_cast<Camera*>(m_entity);
    }
    virtual void on_update(float delta [[maybe_unused]] ) override {
        TransformComponent& transform = m_camera->get_component<TransformComponent>();
        glm::vec3 front = transform.front();
        glm::vec3 right = transform.right();

        glm::vec3 move;

        if (is_key_down(ENGINE_KEY_D)) {
            move += right;
        }
        if (is_key_down(ENGINE_KEY_W)) {
            move += glm::vec3{ front.x, 0, front.z };
        }
        if (is_key_down(ENGINE_KEY_A)) {
            move -= right;
        }
        if (is_key_down(ENGINE_KEY_S)) {
            move -= glm::vec3{ front.x, 0, front.z };
        }

        move /= move.length();
        move *= 0.3;
        transform.translate(move.x, move.y, move.z);

        double xpos;
        double ypos;
        cursor_pos(&xpos, &ypos);

        double xoff = xpos - m_lastx;
        double yoff = m_lasty - ypos;
        m_lastx = xpos;
        m_lasty = ypos;

        if (first) {
            first = false;
            return;
        }

        transform.rotate_custom(yoff * 0.2f, right);
        transform.rotateY(-xoff * 0.2f);
    }
};

}  // namespace Engine