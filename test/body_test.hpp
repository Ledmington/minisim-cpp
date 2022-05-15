#ifndef BODY_TEST_HPP
#define BODY_TEST_HPP

#include "../lib/minunit.h"

MU_TEST(simple) {
    mu_check(1);
}

MU_TEST_SUITE(body_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(simple);
}

#endif // BODY_TEST_HPP