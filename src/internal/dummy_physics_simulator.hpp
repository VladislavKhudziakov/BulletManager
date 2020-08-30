

#pragma once

#include <interfaces/bullets_physics_simulator.hpp>

namespace bullet_manager
{
    class dummy_physics_simulator : public interfaces::bullets_physics_simulator
    {
    public:
        ~dummy_physics_simulator() override = default;
        virtual void process_bullet(float delta, ::bullet_manager::bullet*) override;
    };
}

