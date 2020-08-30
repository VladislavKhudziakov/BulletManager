

#include "dummy_physics_simulator.hpp"

#include <internal/bullet.hpp>

void bullet_manager::dummy_physics_simulator::process_bullet(float delta, ::bullet_manager::bullet* bullet)
{
    bullet->pos = {float(rand() % 800), float(rand() % 600)};
}
