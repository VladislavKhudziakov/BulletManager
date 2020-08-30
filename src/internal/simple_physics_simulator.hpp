

#pragma once

#include <interfaces/bullets_physics_simulator.hpp>
#include <internal/wall.hpp>
#include <internal/concurrent_queue.hpp>

#include <vector>
#include <thread>


namespace bullet_manager
{
    class simple_physics_simulator : public interfaces::bullets_physics_simulator
    {
    public:
        explicit simple_physics_simulator(std::vector<std::unique_ptr<wall>>& walls_list);

        simple_physics_simulator(const simple_physics_simulator&) = delete;
        simple_physics_simulator& operator=(const simple_physics_simulator&) = delete;
        simple_physics_simulator(const simple_physics_simulator&&) = delete;
        simple_physics_simulator& operator=(const simple_physics_simulator&&) = delete;

        ~simple_physics_simulator() override;

        virtual void process_bullet(float delta, ::bullet_manager::bullet*) override;

        template<typename Visitor>
        void visit_walls_list(Visitor v)
        {
            std::lock_guard lock(m_walls_mutex);
            v(m_walls_list.begin(), m_walls_list.end());
        }

    private:
        math::vec2 calculate_bullet_reflection_dir(bullet*, wall*);

        std::vector<std::unique_ptr<wall>> m_walls_list;
        concurrent_queue<std::unique_ptr<wall>> m_spawn_walls_queue;
        std::atomic_bool m_is_alive = true;
        std::mutex m_walls_mutex;
        std::thread m_queue_thread;
    };
} // namespace bullet_manager
