

#include "simple_physics_simulator.hpp"

#include <internal/bullet.hpp>
#include <internal/math.hpp>
#include <internal/walls_manager.hpp>

using namespace bullet_manager;

simple_physics_simulator::simple_physics_simulator(walls_manager* walls_manager)
    : m_walls_manager(walls_manager)
{
}


void simple_physics_simulator::process_bullet(float delta, bullet_manager::bullet* bullet)
{
    m_walls_manager->visit_walls([this, bullet](auto begin, auto end) {
        for (; begin != end; ++begin) {
            const auto wall_len = math::distance(begin->get()->begin_point, begin->get()->end_point);
            const auto d1 = math::distance(bullet->pos, begin->get()->begin_point);
            const auto d2 = math::distance(bullet->pos, begin->get()->end_point);
            const auto sum = d1 + d2;

            if ((sum) >= wall_len - 0.05 && (sum) <= wall_len + 0.05) {
                m_walls_manager->schedule_wall_removing(begin->get());
                bullet->dir = calculate_bullet_reflection_dir(bullet, begin->get());
            }
        }
    });

    auto dir = math::normalize(bullet->dir);
    bullet->pos += dir * bullet->speed * delta;
}


math::vec2 bullet_manager::simple_physics_simulator::calculate_bullet_reflection_dir(
    bullet_manager::bullet* bullet,
    bullet_manager::wall* wall)
{
    const auto dir = math::normalize(bullet->dir);
    const auto v = math::normalize(wall->end_point - wall->begin_point);

    const auto ortho_ccw = math::ortho(v);

    float angle_ccw = math::dot(dir, ortho_ccw);

    if (angle_ccw >= 0 && angle_ccw <= M_PI) {
        return dir - 2 * angle_ccw * ortho_ccw;
    } else {
        const auto ortho_cw = math::ortho(v, false);
        return dir - 2 * math::dot(dir, ortho_cw) * ortho_cw;
    }
}
