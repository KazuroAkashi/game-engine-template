#include <app.h>

int main() {
    const Engine::StartOptions options = {
        .window_width = 1280,
        .window_height = 720,
        .window_title = "Testing",
        .batch_max_quads = 10000
    };

    bool success = Engine::start(options);

    if (success) {
        Engine::loop();
    }

    Engine::destroy();

    return 0;
}