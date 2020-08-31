#include <SFML/Graphics.hpp>

#include <internal/sfml/sfml_renderer.hpp>
#include <internal/sfml/sfml_circle_bullet.hpp>
#include <internal/sfml/sfml_wall.hpp>
#include <internal/bullet_manager.hpp>
#include <internal/misc/simple_physics_simulator.hpp>
#include <internal/misc/walls_manager.hpp>

#include <thread>

bullet_manager::math::vec2 walls_positions[][2]{
    {
        {50, 50},
        {50, 550},
    },
    {
        {50, 550},
        {750, 550},
    },
    {
        {750, 550},
        {750, 50},
    },
    {
        {750, 50},
        {50, 50},
    },
    {
        {150, 450},
        {400, 100},
    },
    {
        {400, 100},
        {650, 450},
    },
    {
        {650, 450},
        {150, 450},
    }};

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

    bullet_manager::sfml_renderer renderer(window);
    bullet_manager::walls_manager walls_manager(&renderer);

    for (const auto& pos : walls_positions) {
        walls_manager.add_wall<bullet_manager::sfml::sfml_wall>(pos[0], pos[1], 3);
    }

    bullet_manager::simple_physics_simulator simulator{&walls_manager};

    bullet_manager::bullet_manager bm(&simulator, &renderer);

    sf::Clock clock;

    std::vector<std::thread> work_threads;
    const auto available_threads = std::thread::hardware_concurrency() - 2;

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
                sleep_time = rand() % 5000;

                auto sz = window.getView().getSize();
                auto dir = bullet_manager::math::normalize({float(rand() % uint32_t(sz.x)), float(rand() % uint32_t(sz.y))});
                dir = dir * 2.f - bullet_manager::math::vec2{1.f, 1.f};
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
        walls_manager.update();

        window.display();
    }

    is_window_open = false;


    for (auto& t : work_threads) {
        t.join();
    }

    return 0;
}
