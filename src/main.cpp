#include <cstdlib>
#include <ctime>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "simulation.hpp"
#include "simulation_builder.hpp"

const double width = 700;
const double height = 700;

const unsigned int nParticles = 1000;

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

void log(std::string msg) {
    std::cout << "[" << currentDateTime() << "]: " << msg << std::endl;
}

int main(void) {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(width, height), "N-bodies simulation");

    Simulation sim = *(SimulationBuilder()
        .nBodies(nParticles)
        .width(width)
        .height(height)
        .gravity(1e-4)
        .friction(0.99)
        .solidBorders()
        .build());

    int i = 0;
    while (window.isOpen()) {
        log("Iteration " + std::to_string(i));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        log("updating");
        sim.update();
        log("drawing");
        window.clear(sf::Color(255, 255, 255, 255));
        sim.render(&window);
        window.display();

        i++;
    }

    return 0;
}