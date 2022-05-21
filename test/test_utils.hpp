#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include "../lib/minunit.h"

#include "../src/v2.hpp"

void assert_v2_eq(V2 a, V2 b) {
    mu_assert_double_eq(a.x, b.x);
    mu_assert_double_eq(a.y, b.y);
}

#endif // TEST_UTILS_HPP