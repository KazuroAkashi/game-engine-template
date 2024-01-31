#pragma once

#include "utils/Memory.hpp"

namespace Engine {

class Platform {
protected:
    virtual bool is_key_down(int) const {
        return false;
    }

    virtual void cursor_pos(double*, double*) const {}

    virtual float get_time() const {
        return 0;
    }

    friend class GameScript;

public:
    virtual bool setup_window(unsigned int, unsigned int, const char*) {
        return false;
    }
    virtual bool window_should_close() {
        return true;
    }
    virtual void loop_logic() {}
    virtual void destroy() {}
};

}  // namespace Engine