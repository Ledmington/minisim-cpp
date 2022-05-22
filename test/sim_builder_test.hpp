#ifndef SIM_BUILDER_TEST_HPP
#define SIM_BUILDER_TEST_HPP

#include "../lib/minunit.h"

#include <SFML/Graphics.hpp>
#include "../src/simulation.hpp"
#include "../src/simulation_builder.hpp"

#include <iostream>

MU_TEST(no_bodies_if_not_specified) {
    Simulation *sim = SimulationBuilder()
        .width(100)
        .height(100)
        .gravity(1e-10)
        .friction(0.99)
        .solidBorders()
        .build();
    mu_check(sim->bodies.size() == 0);
    delete sim;
}

MU_TEST(correct_number_of_bodies) {
    Simulation *sim = SimulationBuilder()
        .nBodies(2)
        .width(100)
        .height(100)
        .gravity(1e-10)
        .friction(0.99)
        .solidBorders()
        .build();
    mu_check(sim->bodies.size() == 2);
    delete sim;
}

MU_TEST_SUITE(sim_builder_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(no_bodies_if_not_specified);
    MU_RUN_TEST(correct_number_of_bodies);
}

#endif // SIM_BUILDER_TEST_HPP