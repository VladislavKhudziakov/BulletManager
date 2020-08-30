

#pragma once


namespace bullet_manager
{
    class bullet;
}

namespace bullet_manager::interfaces
{
    class bullets_physics_simulator
    {
    public:
        virtual ~bullets_physics_simulator() = default;
        virtual void process_bullet(float delta, bullet_manager::bullet*) = 0;
    };
} // namespace bullet_manager::interfaces
