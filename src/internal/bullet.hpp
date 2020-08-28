

#pragma once

#include <internal/misc.hpp>

namespace bullet_manager
{
    class bullet
    {
    public:
        virtual ~bullet() = default;

        misc::vec2 pos {0, 0};
        misc::vec2 dir {0, 0};
        float speed {0};
        float time_spawn {0};
        float life_time {0};
    };
}

