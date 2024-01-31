#include <Camera3D.hpp>
#include <Scene.hpp>
#include <Application.hpp>
#include <entity/ScriptComponent.hpp>
#include <entity/MeshComponent.hpp>
#include <helpers/FirstPersonWalkingCamera.hpp>
#include <entity/Vertex.hpp>
#include <utils/debug.hpp>
#include <events/EventBus.hpp>
#include <events/ViewportLayer.hpp>

int main() {

    {
        Engine::EventBus eventbus;
        Engine::ViewportLayer viewportLayer;
        eventbus.add_layer(&viewportLayer);

        Engine::Scene first_scene;

        const Engine::Application app(&first_scene, &eventbus);

        bool success = app.start(1280, 720, "Testing");
        if (!success) {
            Engine::log("Application could not be started", Engine::LogLevel::ERROR);

            app.destroy();

            return -1;
        }

        Engine::Camera3D camera(&first_scene, 45.0f, 16.0f / 9.0f);

        camera.transform().set_position(1, 0, 0);

        camera.add_component<Engine::ScriptComponent>(&camera).bind<Engine::FirstPersonWalkingCamera>();

        Engine::Vertex vertices[] = {
            {1.0f, 1.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {1.0f, -1.0f, 1.0f},

            {1.0f, 1.0f, -1.0f},
            {-1.0f, 1.0f, -1.0f},
            {-1.0f, -1.0f, -1.0f},
            {1.0f, -1.0f, -1.0f},
        };

        unsigned int indices[] = {
            0, 1, 2, 0, 2, 3,
            0, 3, 4, 3, 4, 7,
            0, 1, 4, 1, 4, 5,
            4, 5, 6, 4, 6, 7,
            1, 5, 6, 1, 2, 6,
            2, 3, 6, 3, 6, 7,
        };

        Engine::Entity entity(&first_scene);
        entity.add_component<Engine::MeshComponent>(vertices, indices, 8u, 6u * 6u);

        entity.transform().set_position(-2, 0, -7);

        Engine::Entity entity2(&first_scene);
        entity2.add_component<Engine::MeshComponent>(vertices, indices, 8u, 6u * 6u);

        entity2.transform().set_rotation(0, 0, -45);
        glm::vec3 up = entity2.transform().up();

        entity2.transform().set_position(2 * up.x + 3, 2 * up.y, 2 * up.z - 8);

        // TODO: Add debug stuff
        // GLint success;
        // GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vs, 1, &vertex_shader, NULL);
        // glCompileShader(vs);
        // glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        // if (!success) {
        //     char infoLog[512];
        //     glGetShaderInfoLog(vs, 512, NULL, infoLog);
        //     std::cout << infoLog << std::endl;
        //     return 1;
        // }

        // GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fs, 1, &fragment_shader, NULL);
        // glCompileShader(fs);
        // glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        // if (!success) {
        //     char infoLog[512];
        //     glGetShaderInfoLog(vs, 512, NULL, infoLog);
        //     std::cout << infoLog << std::endl;
        //     return 1;
        // }

        // TODO: Abstract program
        first_scene.prepare();

        Engine::Shader vert_shader(Engine::ShaderType::VERTEX_SHADER, "assets/shaders/basic_vertex.glsl");

        Engine::Shader frag_shader(Engine::ShaderType::FRAGMENT_SHADER, "assets/shaders/basic_fragment.glsl");

        first_scene.attach_shader(vert_shader);
        first_scene.attach_shader(frag_shader);

        app.loop();
    }

    return 0;
}