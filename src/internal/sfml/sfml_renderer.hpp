

#pragma once

#include <interfaces/renderer.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace bullet_manager
{
    class sfml_renderer : public interfaces::renderer
    {
    public:
        explicit sfml_renderer(sf::RenderTarget&);
        ~sfml_renderer() override = default;
        void draw(bullet_manager::interfaces::renderable& renderable) override;

    private:
        sf::RenderTarget& m_render_target;
    };
} // namespace bullet_manager
