#include "../lib/minunit.h"

#include <SFML/Graphics.hpp>
#include "../src/simulation.hpp"

MU_TEST(two_bodies) {
	Simulation sim(2, 100, 100);

    const float up = 40;
    const float down = 30;
    const float left = 20;
    const float right = 30;

    sf::Vertex *first = &sim.points[0];
    sf::Vertex *second = &sim.points[1];

    first->position.x = left;
    second->position.x = right;

    first->position.y = down;
    second->position.y = up;

    sim.update();

    mu_check(first->position.x > left);
    mu_check(second->position.x < right);
    mu_check(first->position.y > down);
    mu_check(second->position.y < up);
}

MU_TEST_SUITE(simulation_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(two_bodies);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(simulation_test);
	MU_REPORT();
	return MU_EXIT_CODE;
}
