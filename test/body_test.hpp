#ifndef BODY_TEST_HPP
#define BODY_TEST_HPP

#include "../lib/minunit.h"

#include "../src/body.hpp"

MU_TEST(default_body) {
    Body b = Body();
    mu_assert_double_eq(b.position.x, 0);
    mu_assert_double_eq(b.position.y, 0);
    mu_assert_double_eq(b.speed.x, 0);
    mu_assert_double_eq(b.speed.y, 0);
    mu_assert_double_eq(b.mass, 1);
    mu_assert_double_eq(b.radius, 1);
}

MU_TEST(two_body_collision) {
    Body a = Body(V2(0,0), V2(0,0), 1, 1);
    Body b = Body(V2(0.5,0.5), V2(0,0), 1, 1);
    mu_check(a.collidesWith(&b));
}

MU_TEST(two_body_no_collision) {
    Body a = Body(V2(0,0), V2(0,0), 1, 1);
    Body b = Body(V2(1,1), V2(0,0), 1, 1);
    mu_check(a.collidesWith(&b));
}

MU_TEST_SUITE(body_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(default_body);
    MU_RUN_TEST(two_body_collision);
    MU_RUN_TEST(two_body_no_collision);
}

#endif // BODY_TEST_HPP