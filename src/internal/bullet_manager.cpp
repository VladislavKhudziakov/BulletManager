

#include "bullet_manager.hpp"


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

    for (auto begin = m_bullets_storage.begin(); begin != m_bullets_storage.end(); begin++) {
        if (begin->get()->time_spawn + begin->get()->life_time < time) {
            m_bullets_storage.erase(begin);
            continue;
        }

        m_physics_simulator->process_bullet(delta, begin->get());

        if (auto* renderable_bullet = dynamic_cast<interfaces::renderable*>(begin->get()); renderable_bullet != nullptr) {
            m_renderer->draw(renderable_bullet);
        }
    }
}
