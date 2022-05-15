#ifndef BODY_TEST_HPP
#define BODY_TEST_HPP

#include "../lib/minunit.h"

#include "../src/body.hpp"

MU_TEST(default_constructor) {
    Body b = Body();
    mu_assert_double_eq(b.position.x, 0);
    mu_assert_double_eq(b.position.y, 0);
}

MU_TEST_SUITE(body_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(default_constructor);
}

#endif // BODY_TEST_HPP