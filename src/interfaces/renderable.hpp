


#pragma once

namespace bullet_manager::interfaces
{
    class renderer;

    class renderable
    {
    public:
        virtual ~renderable() = default;
        virtual void draw(renderer*) = 0;
    };
} // namespace bullet_manager::interfaces
