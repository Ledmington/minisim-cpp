#include <cstdlib>
#include <ctime>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "simulation.hpp"

const float width = 700;
const float height = 700;

const unsigned int nParticles = 1000;

int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(width, height), "N-bodies simulation");

    Simulation sim(nParticles, width, height);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sim.update();

        window.clear();
        window.draw(sim.points, nParticles, sf::Points);
        window.display();

        /*
        std::cout << "pos: " << sim.points[0].position.x << ", " << sim.points[0].position.y << std::endl;
        std::cout << "speed: " << sim.speed[0].x << ", " << sim.speed[0].y << std::endl;
        std::cout << "acc: " << sim.acc[0].x << ", " << sim.acc[0].y << std::endl;
        std::cout << "force: " << sim.force[0].x << ", " << sim.force[0].y << std::endl;
        std::cout << "-----" << std::endl;
        */
    }

    return 0;
}