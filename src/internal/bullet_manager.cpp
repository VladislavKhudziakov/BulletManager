

#include "bullet_manager.hpp"

#include <vector>


bullet_manager::bullet_manager::bullet_manager(
    ::bullet_manager::interfaces::bullets_physics_simulator* simulator,
    ::bullet_manager::interfaces::renderer* renderer)
    : m_physics_simulator(simulator)
    , m_renderer(renderer)
{
}


void bullet_manager::bullet_manager::update(float time)
{
    const auto delta = time - m_last_time_stamp;
    m_last_time_stamp = time;

    std::lock_guard lock(m_storage_mutex);

    std::vector<decltype(m_bullets_storage)::iterator> expired_bullets;
    expired_bullets.reserve(10);

    for (auto begin = m_bullets_storage.begin(); begin != m_bullets_storage.end(); begin++) {
        if (begin->get()->time_spawn > time) {
            continue;
        }

        if (begin->get()->time_spawn + begin->get()->life_time < time) {
            expired_bullets.emplace_back(begin);
            continue;
        }

        m_physics_simulator->process_bullet(delta, begin->get());

        if (auto* renderable_bullet = dynamic_cast<interfaces::renderable*>(begin->get())) {
            m_renderer->draw(renderable_bullet);
        }
    }

    for (const auto bullet : expired_bullets) {
        m_bullets_storage.erase(bullet);
    }
}
