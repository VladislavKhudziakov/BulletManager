

#pragma once

#include <internal/bullet.hpp>
#include <internal/sfml/sfml_renderable.hpp>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

namespace bullet_manager
{
    class sfml_circle_bullet : public bullet, public sfml_renderable
    {
    public:
        explicit sfml_circle_bullet(float radius, sf::Color color = sf::Color::Black);
        ~sfml_circle_bullet() override = default;

        float get_radius() const;
        void set_radius(float);

        sf::Color get_color() const;
        void set_color(sf::Color);

    private:
        mutable sf::CircleShape m_circle;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
} // namespace bullet_manager
