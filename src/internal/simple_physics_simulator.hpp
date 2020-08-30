

#pragma once

#include <interfaces/bullets_physics_simulator.hpp>
#include <internal/wall.hpp>

#include <vector>


namespace bullet_manager
{
    class simple_physics_simulator : public interfaces::bullets_physics_simulator
    {
    public:
        explicit simple_physics_simulator(std::vector<std::unique_ptr<wall>>& walls_list);
        ~simple_physics_simulator() override = default;
        virtual void process_bullet(float delta, ::bullet_manager::bullet*) override;

    private:
        math::vec2 calculate_bullet_reflection_dir(bullet*, wall*);

        std::vector<std::unique_ptr<wall>>& m_walls_list;
    };
} // namespace bullet_manager
