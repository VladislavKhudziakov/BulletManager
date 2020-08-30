

#include "sfml_circle_bullet.hpp"

#include <SFML/Graphics/RenderTarget.hpp>


bullet_manager::sfml_circle_bullet::sfml_circle_bullet(
    math::vec2 pos, math::vec2 dir, float speed, float time_spawn, float life_time, float radius, sf::Color color)
    : bullet(pos, dir, speed, time_spawn, life_time)
    , m_circle(radius)
{
    set_color(color);
    m_circle.setOrigin(sf::Vector2f(radius, radius));
}


void bullet_manager::sfml_circle_bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_circle.setPosition(pos);
    target.draw(m_circle);
}


float bullet_manager::sfml_circle_bullet::get_radius() const
{
    return m_circle.getRadius();
}


void bullet_manager::sfml_circle_bullet::set_radius(float radius)
{
    m_circle.setRadius(radius);
}


sf::Color bullet_manager::sfml_circle_bullet::get_color() const
{
    return m_circle.getFillColor();
}


void bullet_manager::sfml_circle_bullet::set_color(sf::Color color)
{
    m_circle.setFillColor(color);
    m_circle.setOutlineColor(color);
}
