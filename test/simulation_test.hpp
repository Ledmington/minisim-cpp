#ifndef SIMULATION_TEST_HPP
#define SIMULATION_TEST_HPP

#include "../lib/minunit.h"

#include <SFML/Graphics.hpp>
#include "../src/simulation.hpp"

#include <iostream>

MU_TEST(two_bodies) {
	Simulation sim(2, 100, 100);

    // the origin (0,0) is at the upper left corner
    // the x axis is placed as usual
    // the y axis points down (so to go "up", you need to decrease the y coordinate)
    const float down = 40;
    const float up = 30;
    const float left = 20;
    const float right = 30;

    Body *first = &sim.bodies[0];
    Body *second = &sim.bodies[1];

    first->position.x = left;
    second->position.x = right;

    first->position.y = down;
    second->position.y = up;

    for(int i=0; i<1000; i++) {
        sim.update();
    }

    /*
    printf("%.10f, %.10f\n", first->position.x, first->position.y);
    printf("%.10f, %.10f\n", sim.speed[0].x, sim.speed[0].y);
    printf("%.10f, %.10f\n", sim.acc[0].x, sim.acc[0].y);
    printf("%.10f, %.10f\n", sim.force[0].x, sim.force[0].x);
    */

    mu_check(first->position.x > left);
    mu_check(second->position.x < right);
    mu_check(first->position.y > down);
    mu_check(second->position.y < up);
}

MU_TEST(can_detect_collisions) {
    Simulation sim = Simulation(100, 100);
    sim.addBody(Body(V2(0,0), V2(0,0), 1, 1));
    sim.addBody(Body(V2(1,1), V2(0,0), 1, 1));
    mu_check(sim.detectAndResolveCollisions());
}

MU_TEST(no_collisions) {
    Simulation sim = Simulation(100, 100);
    sim.addBody(Body(V2(0,0), V2(0,0), 1, 1));
    sim.addBody(Body(V2(2,2), V2(0,0), 1, 1));
    mu_check(!sim.detectAndResolveCollisions());
}

MU_TEST(can_resolve_collisions) {
    Simulation sim = Simulation(100, 100);
    sim.addBody(Body(V2(0,0), V2(0,0), 1, 1));
    sim.addBody(Body(V2(1,0), V2(0,0), 1, 1));
    mu_check(sim.detectAndResolveCollisions());
    mu_check(!sim.detectAndResolveCollisions());
    mu_check(sim.bodies[0].position.x < 0);
    mu_check(sim.bodies[0].position.x > 1);
}

MU_TEST_SUITE(simulation_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(two_bodies);
    MU_RUN_TEST(can_detect_collisions);
    MU_RUN_TEST(no_collisions);
    MU_RUN_TEST(can_resolve_collisions);
}

#endif // SIMULATION_TEST_HPP