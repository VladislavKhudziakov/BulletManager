

#include "sfml_wall.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>


using namespace bullet_manager::sfml;


void sfml_wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // we cannot draw lines in sfml, so... just draw tight rectangle :)
    const auto v = end_point - begin_point;
    float angle = std::atan2(v.y, v.x);
    m_line_view.setRotation(angle * 180.f / M_PI);
    m_line_view.setSize({math::length(v), m_width});
    m_line_view.setFillColor(sf::Color::Black);
    m_line_view.setPosition(begin_point + v / 2.f);
    m_line_view.setOrigin(m_line_view.getSize() / 2.f);
    target.draw(m_line_view);
}


sfml_wall::sfml_wall(math::vec2 begin_point, math::vec2 end_point, float width, sf::Color color)
    : wall(begin_point, end_point)
    , m_width(width)
{
    set_color(color);
    m_line_view.setOutlineThickness(0);
}


float sfml_wall::get_width() const
{
    return m_width;
}


void sfml_wall::set_width(float w)
{
    m_width = w;
}


sf::Color sfml_wall::get_color() const
{
    return m_line_view.getFillColor();
}


void sfml_wall::set_color(sf::Color color)
{
    m_line_view.setFillColor(color);
    m_line_view.setOutlineColor(color);
}
