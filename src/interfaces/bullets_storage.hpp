

#pragma once

#include <deque>
#include <internal/bullet.hpp>


namespace bullet_manager::interfaces
{
    template<
        typename BulletType,
        template<typename T = BulletType, typename = std::allocator<T>> typename StorageType = std::deque>
    class bullets_storage
    {
    public:
        virtual ~bullets_storage() = default;

        virtual void add_bullet(BulletType) = 0;
        virtual void erase_bullet(BulletType) = 0;
        virtual StorageType<BulletType> get_bullets() const = 0;
    };

    template<
        typename BulletType,
        template<typename T = BulletType, typename = std::allocator<T>> class StorageType = std::deque>
    using bullets_storage_uptr = std::unique_ptr<bullets_storage<BulletType, StorageType>>;

    template<
        typename BulletType,
        template<typename T = BulletType, typename = std::allocator<T>> typename StorageType = std::deque>
    using bullets_storage_sptr = std::shared_ptr<bullets_storage<BulletType, StorageType>>;

    template<
        typename BulletType,
        template<typename T = BulletType, typename = std::allocator<T>> typename StorageType = std::deque>
    using bullets_storage_wptr = std::weak_ptr<bullets_storage<BulletType, StorageType>>;
} // namespace bullet_manager::interfaces
