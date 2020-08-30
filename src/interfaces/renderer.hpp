

#pragma once


namespace bullet_manager::interfaces
{
    class renderable;

    class renderer
    {
    public:
        virtual ~renderer() = default;
        virtual void draw(renderable*) = 0;
    };
} // namespace src::interfaces
