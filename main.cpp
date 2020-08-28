#include <SFML/Graphics.hpp>

#include <interfaces/renderer.hpp>
#include <interfaces/renderable.hpp>
#include <internal/sfml/sfml_renderer.hpp>
#include <internal/sfml/sfml_renderable.hpp>
#include <internal/sfml/sfml_circle_bullet.hpp>
#include <internal/sfml/sfml_wall.hpp>


int main()
{
    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window", sf::Style::Default, settings);

    bullet_manager::sfml_circle_bullet bullet(5);

    bullet_manager::sfml_wall wall(3);
    wall.begin_point = {0, 0};
    wall.end_point = {100, 100};

    bullet.pos = {400, 300};

    bullet_manager::sfml_renderer renderer(window);

    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(0, 0);
    lines[0].color = sf::Color::Black;
    lines[1].position = sf::Vector2f(100, 100);
    lines[0].color = sf::Color::Black;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::White);

        // draw everything here...
        renderer.draw(bullet);
        renderer.draw(wall);

//         window.draw(circle);

        // end the current frame
        window.display();
    }

    return 0;
}
