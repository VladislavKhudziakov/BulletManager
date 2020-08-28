


#pragma once

#include <interfaces/renderable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace bullet_manager
{
    class sfml_renderable : public interfaces::renderable, private sf::Drawable
    {
        friend class sfml_renderer;

    public:
        ~sfml_renderable() override = default;
        void draw(interfaces::renderer& renderer) override;
    };
} // namespace bullet_manager
