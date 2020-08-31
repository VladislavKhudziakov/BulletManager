

#pragma once

#include <interfaces/renderable.hpp>
#include <internal/misc/math.hpp>

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
        bullet(math::vec2, math::vec2, float, float, float);

        virtual ~bullet() = default;

        math::vec2 pos{0, 0};
        math::vec2 dir{0, 0};
        float speed{0};
        float time_spawn{0};
        float life_time{0};
    };
} // namespace bullet_manager
