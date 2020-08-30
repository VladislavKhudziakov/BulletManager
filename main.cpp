#include <SFML/Graphics.hpp>

#include <internal/sfml/sfml_renderer.hpp>
#include <internal/sfml/sfml_circle_bullet.hpp>
#include <internal/sfml/sfml_wall.hpp>
#include <internal/bullet_manager.hpp>
#include <internal/dummy_physics_simulator.hpp>

#include <thread>


int main()
{
    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "My window",
        sf::Style::Default,
        settings);

    std::atomic_bool is_window_open = true;

    bullet_manager::sfml_circle_bullet bullet({400, 300}, {0, 0}, 0, 0, 0, 5);

    bullet_manager::sfml_renderer renderer(window);
    bullet_manager::dummy_physics_simulator simulator{};

    bullet_manager::bullet_manager bm(&simulator, &renderer);

    bullet_manager::sfml_wall wall(3);
    wall.begin_point = {0, 0};
    wall.end_point = {100, 100};
    sf::Clock clock;

    std::vector<std::thread> work_threads;
    const auto available_threads = std::thread::hardware_concurrency() - 1;

    work_threads.reserve(available_threads);

    for (size_t i = 0; i < available_threads; ++i) {
        work_threads.emplace_back([&bm, &clock, &window, &is_window_open]() {
            while (is_window_open) {
                auto sleep_time = rand() % 1000;
                std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
                auto sz = window.getSize();
                bm.fire<bullet_manager::sfml_circle_bullet>(
                    bullet_manager::misc::vec2 {float(rand() % uint32_t(sz.x)), float(rand() % uint32_t(sz.y))},
                    bullet_manager::misc::vec2 {float(rand() % uint32_t(sz.x)), float(rand() % uint32_t(sz.y))},
                    0, clock.getElapsedTime().asSeconds(), 1, 3);
            }
        });
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
                break;
        }

        window.clear(sf::Color::White);

        bm.update(clock.getElapsedTime().asSeconds());

        window.display();
    }

    is_window_open = false;


    for (auto& t : work_threads) {
        t.join();
    }

    return 0;
}
