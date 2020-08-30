

#include "bullet.hpp"

using namespace bullet_manager;

bullet::bullet(misc::vec2 pos, misc::vec2 dir, float speed, float time_spawn, float life_time)
    : pos(pos)
    , dir(dir)
    , speed(speed)
    , time_spawn(time_spawn)
    , life_time(life_time)
{
}
