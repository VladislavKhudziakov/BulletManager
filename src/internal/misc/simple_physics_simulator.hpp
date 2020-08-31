

#pragma once

#include <interfaces/bullets_physics_simulator.hpp>
#include <internal/wall.hpp>

namespace bullet_manager
{
    class walls_manager;

    class simple_physics_simulator : public interfaces::bullets_physics_simulator
    {
    public:
        explicit simple_physics_simulator(walls_manager*);
        ~simple_physics_simulator() override = default;

        virtual void process_bullet(float delta, ::bullet_manager::bullet*) override;

    private:
        math::vec2 calculate_bullet_reflection_dir(bullet*, wall*);
        walls_manager* m_walls_manager;
    };
} // namespace bullet_manager
