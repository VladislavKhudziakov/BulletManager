
#pragma once

#include <internal/misc/math.hpp>

namespace bullet_manager
{
    class wall
    {
    public:
        wall(math::vec2 begin_point, math::vec2 end_point);
        virtual ~wall() = default;

        math::vec2 begin_point;
        math::vec2 end_point;
    };
} // namespace bullet_manager
