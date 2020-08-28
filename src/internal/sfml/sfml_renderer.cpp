

#include "sfml_renderer.hpp"

#include <interfaces/renderable.hpp>
#include <internal/sfml/sfml_renderable.hpp>


bullet_manager::sfml_renderer::sfml_renderer(sf::RenderTarget& rt)
    : m_render_target(rt)
{
}

void bullet_manager::sfml_renderer::draw(interfaces::renderable& renderable)
{
    m_render_target.draw(static_cast<sfml_renderable&>(renderable));
}
