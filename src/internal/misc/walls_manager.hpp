

#pragma once

#include <interfaces/renderer.hpp>
#include <internal/misc/concurrent_queue.hpp>

#include <deque>
#include <thread>

namespace bullet_manager
{
    class wall;

    class walls_manager
    {
    public:
        explicit walls_manager(interfaces::renderer*);
        walls_manager(const walls_manager&) = delete;
        walls_manager& operator=(const walls_manager&) = delete;
        walls_manager(const walls_manager&&) = delete;
        walls_manager& operator=(const walls_manager&&) = delete;
        ~walls_manager();

        void schedule_wall_removing(wall*);

        template<typename WallType, typename... Args>
        void add_wall(Args&&... args)
        {
            std::lock_guard lock(m_walls_list_mutex);
            m_walls_list.emplace_back(std::make_unique<WallType>(std::forward<Args>(args)...));
        }

        void update();

        template<typename Visitor>
        void visit_walls(Visitor v)
        {
            std::lock_guard lock(m_walls_list_mutex);
            v(m_walls_list.begin(), m_walls_list.end());
        }

    private:
        std::mutex m_walls_list_mutex;
        std::mutex m_walls_to_remove_mutex;
        std::atomic_bool m_is_alive = true;
        std::thread m_spawn_thread;
        std::deque<std::unique_ptr<wall>> m_walls_list;
        concurrent_queue<std::unique_ptr<wall>> m_spawn_walls_queue;
        std::vector<wall*> m_walls_to_remove;

        interfaces::renderer* m_renderer;
    };
} // namespace bullet_manager
