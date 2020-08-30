#include <SFML/Graphics.hpp>

#include <internal/sfml/sfml_renderer.hpp>
#include <internal/sfml/sfml_circle_bullet.hpp>
#include <internal/sfml/sfml_wall.hpp>
#include <internal/bullet_manager.hpp>
#include <internal/simple_physics_simulator.hpp>
#include <interfaces/renderable.hpp>

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

    std::vector<std::unique_ptr<bullet_manager::wall>> walls {};

    for (size_t i = 0; i < 10; ++i) {
        walls.emplace_back(std::make_unique<bullet_manager::sfml::sfml_wall>(3));
    }

    walls[0]->begin_point = {50, 50};
    walls[0]->end_point = {50, 550};

    walls[1]->begin_point = {50, 550};
    walls[1]->end_point = {750, 550};

    walls[2]->begin_point = {750, 550};
    walls[2]->end_point = {750, 50};

    walls[3]->begin_point = {750, 50};
    walls[3]->end_point = {50, 50};

    walls[4]->begin_point = {150, 450};
    walls[4]->end_point = {400, 100};

    walls[5]->begin_point = {400, 100};
    walls[5]->end_point = {650, 450};

    walls[6]->begin_point = {650, 450};
    walls[6]->end_point = {150, 450};

    bullet_manager::sfml_renderer renderer(window);
    bullet_manager::simple_physics_simulator simulator{walls};

    ::bullet_manager::bullet_manager bm(&simulator, &renderer);

    bullet_manager::sfml::sfml_wall wall(3);
    wall.begin_point = {0, 0};
    wall.end_point = {100, 100};
    sf::Clock clock;

    std::vector<std::thread> work_threads;
    const auto available_threads = std::thread::hardware_concurrency() - 1;

    work_threads.reserve(available_threads);

    for (size_t i = 0; i < available_threads; ++i) {
        work_threads.emplace_back([&bm, &clock, &window, &is_window_open]() {
            float timer = clock.getElapsedTime().asSeconds();

            auto sleep_time = rand() % 10000;

            while (is_window_open) {
                float curr_time_stamp = clock.getElapsedTime().asSeconds();
                auto ms = std::chrono::milliseconds(sleep_time);
                auto seconds = std::chrono::duration_cast<std::chrono::seconds>(ms).count();

                if (curr_time_stamp <= timer + seconds) {
                    continue;
                }

                timer = curr_time_stamp;
                sleep_time = rand() % 10000;

                auto sz = window.getView().getSize();
                auto dir = bullet_manager::math::normalize({float(rand() % uint32_t(sz.x)), float(rand() % uint32_t(sz.y))});
                dir = dir * 2.f - bullet_manager::math::vec2 {1.f, 1.f};
                bm.fire<bullet_manager::sfml_circle_bullet>(
                    bullet_manager::math::vec2{float(rand() % uint32_t(sz.x)), float(rand() % uint32_t(sz.y))},
                    bullet_manager::math::vec2{dir},
                    rand() % 1000,
                    clock.getElapsedTime().asSeconds(),
                    rand() % 10,
                    3);
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

        for (auto& wall : walls) {
            if (auto renderable_wall = dynamic_cast<bullet_manager::interfaces::renderable*>(wall.get())) {
                renderer.draw(renderable_wall);
            }
        }

        window.display();
    }

    is_window_open = false;


    for (auto& t : work_threads) {
        t.join();
    }

    return 0;
}
