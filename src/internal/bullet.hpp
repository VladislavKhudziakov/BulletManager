

#pragma once

#include <internal/misc.hpp>

#include <memory>

namespace bullet_manager
{
    class bullet;

    using bullet_uptr = std::unique_ptr<bullet>;
    using bullet_sptr = std::shared_ptr<bullet>;
    using bullet_wptr = std::weak_ptr<bullet>;

    class bullet
    {
    public:
        static bullet_sptr create()
        {
            return std::make_shared<bullet>();
        }

        virtual ~bullet() = default;

        misc::vec2 pos {0, 0};
        misc::vec2 dir {0, 0};
        float speed {0};
        float time_spawn {0};
        float life_time {0};
    };
}

