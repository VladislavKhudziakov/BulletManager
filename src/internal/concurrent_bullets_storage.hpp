


#pragma once

#include <deque>

#include <interfaces/bullets_storage.hpp>
#include <internal/bullet.hpp>

#include <mutex>



namespace bullet_manager
{
    template <typename BulletType, template<typename T = BulletType, typename = std::allocator<T>> typename StorageType = std::deque>
    class concurrent_bullets_storage : public interfaces::bullets_storage<bullet_sptr, StorageType>
    {
    public:
        static std::unique_ptr<concurrent_bullets_storage> create()
        {
            return std::make_unique<concurrent_bullets_storage>();
        }

        void add_bullet(BulletType bullet) override
        {
            std::lock_guard lock(m_storage_mutex);
            m_storage.emplace_back(bullet);
        }

        void erase_bullet(BulletType bullet) override
        {
            std::lock_guard lock(m_storage_mutex);
            m_storage.erase(std::remove(m_storage.begin(), m_storage.end(), bullet));
        }

        StorageType<BulletType> get_bullets() const override
        {
            StorageType<bullet_sptr> res;

            {
                std::lock_guard lock(m_storage_mutex);
                res = m_storage;
            }

            return res;
        }

    private:
        mutable std::mutex m_storage_mutex;
        StorageType<bullet_sptr> m_storage;
    };
}

