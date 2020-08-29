

#pragma once

#include <interfaces/bullets_storage.hpp>
#include <interfaces/bullets_physics_simulator.hpp>

#include <internal/misc.hpp>

#include <chrono>
#include <type_traits>


namespace bullet_manager
{
    template<typename BulletType>
    class bullet_manager
    {
    public:
        bullet_manager(
            interfaces::bullets_storage_uptr<BulletType> bullets_storage,
            interfaces::bullets_physics_simulator_uptr<BulletType> physics_simulator)
            : m_bullets_storage(std::move(bullets_storage))
            , m_physics_simulator(std::move(physics_simulator))
        {
        }

        void update(float time)
        {
            const auto delta = time - m_last_time_stamp;
            auto bullets = m_bullets_storage->get_bullets();
            m_physics_simulator->process_bullets(delta, bullets.begin(), bullets.end());
            m_last_time_stamp = time;
        }

        template<typename CreatedBulletType, typename... Args>
        void fire(misc::vec2 pos, misc::vec2 dir, float speed, float time, float life_time, Args&&... args)
        {
            auto bullet = CreatedBulletType::create(std::forward<Args>(args)...);

            bullet->pos = pos;
            bullet->dir = dir;
            bullet->speed = speed;
            bullet->time = time;
            bullet->life_time = life_time;

            m_bullets_storage->add_bullet(bullet);
        }

    private:
        interfaces::bullets_storage_uptr<BulletType> m_bullets_storage;
        interfaces::bullets_physics_simulator_uptr<BulletType> m_physics_simulator;
        float m_last_time_stamp = 0;
    };
} // namespace bullet_manager
