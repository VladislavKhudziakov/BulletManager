
#pragma once

#include <internal/math.hpp>

namespace bullet_manager
{
    class wall
    {
    public:
        virtual ~wall() = default;

        math::vec2 begin_point;
        math::vec2 end_point;
    };
} // namespace bullet_manager
