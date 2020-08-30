
#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace bullet_manager::math
{
    using vec2 = sf::Vector2f;

    inline float length(vec2 v)
    {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    inline vec2 normalize(vec2 v)
    {
        auto len = length(v);
        return {v.x / len, v.y / len};
    }

    inline float distance(vec2 from, vec2 to)
    {
        return length(to - from);
    }

    inline vec2 ortho(vec2 v, bool ccw = true)
    {
        return ccw ? vec2{v.y, -v.x} : vec2{-v.y, v.x};
    }

    inline float dot(vec2 v1, vec2 v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
} // namespace bullet_manager::math
