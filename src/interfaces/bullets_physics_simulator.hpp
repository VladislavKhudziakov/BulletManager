

#pragma once


namespace bullet_manager::interfaces
{
    template<typename BulletType>
    class bullets_physics_simulator
    {
    public:
        virtual ~bullets_physics_simulator() = default;

        template<typename FwdIter>
        void process_bullets(float delta, FwdIter begin, FwdIter end)
        {
            for (; begin != end; ++begin) {
                process_bullet(*begin);
            }
        }

    protected:
        virtual void process_bullet(BulletType) = 0;
    };

    template<typename BulletType>
    using bullets_physics_simulator_uptr = std::unique_ptr<bullets_physics_simulator<BulletType>>;

    template<typename BulletType>
    using bullets_physics_simulator_sptr = std::shared_ptr<bullets_physics_simulator<BulletType>>;

    template<typename BulletType>
    using bullets_physics_simulator_wptr = std::weak_ptr<bullets_physics_simulator<BulletType>>;
} // namespace bullet_manager::interfaces
