

#pragma once

#include <deque>
#include <mutex>
#include <condition_variable>
#include <queue>

namespace bullet_manager
{
    template<typename T>
    class concurrent_queue
    {
    public:
        template<typename... Args>
        void emplace(Args&&... args)
        {
            std::lock_guard lock(m_mutex);
            m_storage.emplace_front(std::forward<Args>(args)...);
            m_cv.notify_one();
        }

        void push(const T& val)
        {
            std::lock_guard lock(m_mutex);
            m_storage.push_front(val);
            m_cv.notify_one();
        }

        void pop(T& ref)
        {
            std::lock_guard lock(m_mutex);

            if(m_storage.empty()) {
                throw std::runtime_error("queue is empty.");
            }

            assign_and_pop(ref);
        }

        void try_pop(T& ref)
        {
            std::unique_lock lock(m_mutex);

            if (!m_storage.empty()) {
                assign_and_pop(ref);
                return;
            }

            m_cv.wait(lock, [this]() {
               return !m_storage.empty();
            });

            assign_and_pop(ref);
        }

    private:
        void assign_and_pop(T& ref)
        {
            ref = std::move(m_storage.back());
            m_storage.pop_back();
        }

        std::mutex m_mutex;
        std::condition_variable m_cv;
        std::deque<T> m_storage;
    };
}

