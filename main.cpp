#include <vector>
#include <string>
#include <memory>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

#include "boid.h"
#include "flock.h"
#include "drawable.h"


int main() {
    srand((int)time(0)); // we're going to use some random numbers, seed it at the beginning

    auto const SCREEN_WIDTH{sf::VideoMode::getDesktopMode().width};
    auto const SCREEN_HEIGHT{sf::VideoMode::getDesktopMode().height};

    auto vm = std::make_unique<sf::VideoMode>(SCREEN_WIDTH, SCREEN_HEIGHT);
    auto window = std::make_unique<sf::RenderWindow>(
            *vm,"Boids",sf::Style::Fullscreen);

    sf::Clock clock;

    const int numBoids = 500;
    auto* flock = new Flock(numBoids);
    flock->randomInit(SCREEN_WIDTH, SCREEN_HEIGHT);

    bool paused = false;

    while (window->isOpen()) {
        sf::Event event;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();

        
        // Clear everything from the last frame
        window->clear();

        if (!paused) {
            flock->calculateCenterOfMassesAndVelocities();
            flock->calculateMutualRepulsion();

            auto enemy = sf::Mouse::getPosition();

            auto elapsed_time = clock.restart(); // elapsed since last restart
            auto elapsed_as_seconds = elapsed_time.asSeconds();

            for (auto &boid: *flock){
                boid.update(elapsed_as_seconds, enemy.x, enemy.y);
            }

        } // end if(!paused)

        // TODO: game scene
        for (auto &boid: *flock) {
            boid.drawOn(*window);
        }


        // Display what was drawn
        window->display();
    }
    delete flock;
    return 0;
}
