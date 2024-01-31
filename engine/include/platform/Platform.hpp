#pragma once

#include "utils/Memory.hpp"
#include "events/EventBus.hpp"

namespace Engine {

class Platform {
protected:
    EventBus* m_eventbus;

    virtual bool is_key_down(int keycode [[maybe_unused]] ) const {
        return false;
    }

    virtual void cursor_pos(double* xpos [[maybe_unused]], double* ypos [[maybe_unused]] ) const {}

    virtual float get_time() const {
        return 0;
    }

    friend class GameScript;

public:
    Platform(EventBus* eventbus): m_eventbus(eventbus) {}

    virtual bool setup_window(unsigned int width [[maybe_unused]], unsigned int height [[maybe_unused]], const char* name [[maybe_unused]] ) {
        return false;
    }
    virtual bool window_should_close() {
        return true;
    }
    virtual void loop_logic() {}
    virtual void destroy() {}
};

}  // namespace Engine