

#include "sfml_renderable.hpp"

#include <interfaces/renderer.hpp>

using namespace bullet_manager;

void sfml_renderable::draw(interfaces::renderer* renderer)
{
    renderer->draw(this);
}
