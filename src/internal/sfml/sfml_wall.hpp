

#pragma once

#include <internal/wall.hpp>
#include <internal/sfml/sfml_renderable.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace bullet_manager::sfml
{
    class sfml_wall : public wall, public sfml_renderable
    {
    public:
        explicit sfml_wall(
            math::vec2 begin_point,
            math::vec2 end_point,
            float width,
            sf::Color color = sf::Color::Black);

        ~sfml_wall() override = default;

        float get_width() const;
        void set_width(float);

        sf::Color get_color() const;
        void set_color(sf::Color);

    private:
        mutable sf::RectangleShape m_line_view;
        float m_width;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
} // namespace bullet_manager::sfml
