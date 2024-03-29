#pragma once

#include "../lib/minunit.h"

#include <SFML/Graphics.hpp>
#include "../src/simulation.hpp"
#include "../src/simulation_builder.hpp"
#include "test_utils.hpp"

Simulation *sim;

static void init() {
    sim = SimulationBuilder()
        .width(100)
        .height(100)
        .gravity(1e-8)
        .friction(0.99)
        .solidBorders()
        .build();
}

static void end() {
    delete sim;
}

MU_TEST(two_bodies) {
    // the origin (0,0) is at the upper left corner
    // the x axis is placed as usual
    // the y axis points down (so to go "up", you need to decrease the y coordinate)
    const float down = 40;
    const float up = 30;
    const float left = 20;
    const float right = 30;

    Body *first = new Body(V2(left, down), V2(0, 0), 1, 1);
    Body *second = new Body(V2(right, up), V2(0, 0), 1, 1);

    sim->addBody(first);
    sim->addBody(second);

    sim->update();

    mu_check(first->position.x > left);
    mu_check(second->position.x < right);
    mu_check(first->position.y < down);
    mu_check(second->position.y > up);
}

MU_TEST(can_detect_collisions) {
    sim->addBody(new Body(V2(1,1), V2(0,0), 1, 1));
    sim->addBody(new Body(V2(2,2), V2(0,0), 1, 1));
    mu_check(sim->detectAndResolveCollisions());
}

MU_TEST(no_collisions) {
    sim->addBody(new Body(V2(1,1), V2(0,0), 1, 1));
    sim->addBody(new Body(V2(3,3), V2(0,0), 1, 1));
    mu_check(!sim->detectAndResolveCollisions());
}

MU_TEST(can_resolve_collisions) {
    sim->addBody(new Body(V2(1,2), V2(0,0), 1, 1));
    sim->addBody(new Body(V2(2,2), V2(0,0), 1, 1));
    mu_check(sim->detectAndResolveCollisions());
    mu_check(!sim->detectAndResolveCollisions());
    assert_v2_eq(sim->bodies[0]->position, V2(0.5, 2));
    assert_v2_eq(sim->bodies[1]->position, V2(2.5, 2));
}

MU_TEST(can_resolve_collisions_different_masses) {
    // this test is a copy-paste of "can_resolve_collisions" because mass
    // must not interfere with collisions
    sim->addBody(new Body(V2(1,2), V2(0,0), 2, 1));
    sim->addBody(new Body(V2(2,2), V2(0,0), 3, 1));
    mu_check(sim->detectAndResolveCollisions());
    mu_check(!sim->detectAndResolveCollisions());
    assert_v2_eq(sim->bodies[0]->position, V2(0.5, 2));
    assert_v2_eq(sim->bodies[1]->position, V2(2.5, 2));
}

MU_TEST(can_resolve_collisions_different_radii) {
    // this test is an adapted copy-paste of "can_resolve_collisions" because
    // radii must not interfere with collisions
    sim->addBody(new Body(V2(4,4), V2(0,0), 1, 2));
    sim->addBody(new Body(V2(5,4), V2(0,0), 1, 3));
    mu_check(sim->detectAndResolveCollisions());
    mu_check(!sim->detectAndResolveCollisions());
    assert_v2_eq(sim->bodies[0]->position, V2(2, 4));
    assert_v2_eq(sim->bodies[1]->position, V2(7, 4));
}

MU_TEST_SUITE(simulation_test) {
	MU_SUITE_CONFIGURE(init, end);

	MU_RUN_TEST(two_bodies);
    MU_RUN_TEST(can_detect_collisions);
    MU_RUN_TEST(no_collisions);
    MU_RUN_TEST(can_resolve_collisions);
    MU_RUN_TEST(can_resolve_collisions_different_masses);
    MU_RUN_TEST(can_resolve_collisions_different_radii);
}