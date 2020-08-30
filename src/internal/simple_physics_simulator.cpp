

#include "simple_physics_simulator.hpp"

#include <internal/bullet.hpp>
#include <internal/math.hpp>

using namespace bullet_manager;


simple_physics_simulator::simple_physics_simulator(std::vector<std::unique_ptr<wall>>& walls_list)
    : m_walls_list(walls_list)
{
}


void simple_physics_simulator::process_bullet(float delta, bullet_manager::bullet* bullet)
{
    for (auto begin = m_walls_list.begin(); begin != m_walls_list.end(); ++begin) {
        const auto wall_len = math::distance(begin->get()->begin_point, begin->get()->end_point);
        const auto d1 = math::distance(bullet->pos, begin->get()->begin_point);
        const auto d2 = math::distance(bullet->pos, begin->get()->end_point);
        const auto sum = d1 + d2;

        if ((sum) >= wall_len - 0.05 && (sum) <= wall_len + 0.05) {
            bullet->dir = calculate_bullet_reflection_dir(bullet, begin->get());
        }
    }

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
    const auto ortho_cw = math::ortho(v, false);

    float angle_ccw = math::dot(ortho_ccw, dir);

    float angle_cw = math::dot(ortho_cw, dir);

    if (angle_ccw >= 0 && angle_ccw <= M_PI) {
        return dir - 2 * math::dot(dir, ortho_ccw) * ortho_ccw;
    }

    if (angle_cw >= 0 && angle_cw <= M_PI) {
        return dir - 2 * math::dot(dir, ortho_cw) * ortho_cw;
    }

    assert(false);
}