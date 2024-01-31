#include <app.h>

int main() {
    bool success = Engine::start(1280, 720, "Testing");

    if (success) {
        Engine::loop();
    }

    Engine::destroy();

    return 0;
}