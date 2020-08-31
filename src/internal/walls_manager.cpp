

#include "walls_manager.hpp"

#include <interfaces/renderable.hpp>
#include <internal/wall.hpp>


bullet_manager::walls_manager::walls_manager(interfaces::renderer* renderer)
    : m_renderer(renderer)
{
    m_spawn_thread = std::thread([this]() {
        while (m_is_alive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::unique_ptr<wall> wall_ptr;
            m_spawn_walls_queue.try_pop(wall_ptr);
            std::lock_guard lock(m_walls_list_mutex);
            m_walls_list.emplace_back(std::move(wall_ptr));
        }
    });
}


bullet_manager::walls_manager::~walls_manager()
{
    m_is_alive = false;
    m_spawn_thread.join();
}


void bullet_manager::walls_manager::schedule_wall_removing(bullet_manager::wall* w)
{
    std::lock_guard lock(m_walls_to_remove_mutex);
    m_walls_to_remove.emplace_back(w);
}

void bullet_manager::walls_manager::update()
{
    std::vector<wall*> walls_to_remove;

    {
        std::lock_guard walls_to_remove_lock(m_walls_to_remove_mutex);
        walls_to_remove = std::move(m_walls_to_remove);
    }

    std::lock_guard lock(m_walls_list_mutex);

    for (const auto wall : walls_to_remove) {
        auto it = std::find_if(m_walls_list.begin(), m_walls_list.end(), [wall](const auto& wall_ptr) {
            return wall_ptr.get() == wall;
        });

        if (it == m_walls_list.end()) {
            continue;
        }

        m_spawn_walls_queue.emplace(std::move(*it));
        m_walls_list.erase(it);
    }

    for (auto& wall : m_walls_list) {
        if (auto renderable_wall = dynamic_cast<interfaces::renderable*>(wall.get())) {
            m_renderer->draw(renderable_wall);
        }
    }
}
