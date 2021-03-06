

#pragma once

#include <interfaces/bullets_physics_simulator.hpp>
#include <interfaces/renderer.hpp>
#include <interfaces/renderable.hpp>

#include <internal/bullet.hpp>
#include <internal/misc/math.hpp>

#include <deque>
#include <mutex>


namespace bullet_manager
{
    class bullet_manager
    {
    public:
        bullet_manager(
            interfaces::bullets_physics_simulator*,
            interfaces::renderer*);

        void update(float time);

        template<typename CreatedBulletType, typename... Args>
        void fire(Args&&... args)
        {
            std::lock_guard lock(m_storage_mutex);
            m_bullets_storage.emplace_back(std::make_unique<CreatedBulletType>(std::forward<Args>(args)...));
        }

    private:
        std::deque<std::unique_ptr<bullet>> m_bullets_storage;
        std::mutex m_storage_mutex;
        interfaces::bullets_physics_simulator* m_physics_simulator;
        interfaces::renderer* m_renderer;
        float m_last_time_stamp = 0;
    };
} // namespace bullet_manager
