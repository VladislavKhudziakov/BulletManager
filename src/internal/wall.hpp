
#pragma once

#include <internal/misc.hpp>

namespace bullet_manager
{
    class wall
    {
    public:
        virtual ~wall() = default;

        misc::vec2 begin_point;
        misc::vec2 end_point;
    };
} // namespace bullet_manager
