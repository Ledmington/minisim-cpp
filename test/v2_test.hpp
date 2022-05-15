#ifndef V2_TEST_HPP
#define V2_TEST_HPP

#include "../lib/minunit.h"

#include "../src/v2.hpp"

MU_TEST(default_is_origin) {
    V2 v = V2();
    mu_assert_double_eq(v.x, 0);
    mu_assert_double_eq(v.y, 0);
}

MU_TEST(simple_add) {
    V2 v = V2();
    V2 w = V2(1, 1);
    V2 r = v.add(w);
    mu_assert_double_eq(r.x, w.x);
    mu_assert_double_eq(r.y, w.y);
}

MU_TEST(simple_sub) {
    V2 v = V2();
    V2 w = V2(1, 1);
    V2 r = v.sub(w);
    mu_assert_double_eq(r.x, -w.x);
    mu_assert_double_eq(r.y, -w.y);
}

MU_TEST(add_sub) {
    V2 v = V2();
    V2 w = V2(1, 1);
    V2 r = v.add(w).sub(w);
    mu_assert_double_eq(r.x, 0);
    mu_assert_double_eq(r.y, 0);
}

MU_TEST(simple_mul) {
    V2 v = V2(1, 2);
    V2 r = v.mul(2);
    mu_assert_double_eq(r.x, 2);
    mu_assert_double_eq(r.y, 4);
}

MU_TEST(simple_div) {
    V2 v = V2(2, 4);
    V2 r = v.div(2);
    mu_assert_double_eq(r.x, 1);
    mu_assert_double_eq(r.y, 2);
}

MU_TEST(mul_div) {
    V2 v = V2(1, 1);
    V2 r = v.mul(2).div(2);
    mu_assert_double_eq(r.x, 1);
    mu_assert_double_eq(r.y, 1);
}

MU_TEST(modulo_of_origin_is_zero) {
    V2 v = V2();
    mu_assert_double_eq(v.mod(), 0);
}

MU_TEST(simple_modulo) {
    V2 v = V2(5, 12);
    mu_assert_double_eq(v.mod(), 13);
}

MU_TEST(dot_with_origin_is_zero) {
    V2 v = V2();
    V2 w = V2(2, 3);
    mu_assert_double_eq(v.dot(w), 0);
}

MU_TEST(normal_dot) {
    V2 v = V2(1, 2);
    V2 w = V2(2, 3);
    mu_assert_double_eq(v.dot(w), 8);
}

MU_TEST(norm_of_origin_is_origin) {
    V2 v = V2();
    V2 n = v.norm();
    mu_assert_double_eq(n.x, 0);
    mu_assert_double_eq(n.y, 0);
}

MU_TEST(vector_norm) {
    V2 v = V2(0, 2);
    V2 n = v.norm();
    mu_assert_double_eq(n.x, 0);
    mu_assert_double_eq(n.y, 1);
}

MU_TEST(normalized_vector_modulo_is_one) {
    V2 v = V2(1.7, 5.3);
    V2 n = v.norm();
    mu_assert_double_eq(n.mod(), 1);
}

MU_TEST(distance_from_origin_is_vector_modulo) {
    V2 v = V2();
    V2 w = V2(1, 2);
    mu_assert_double_eq(w.dist(v), w.mod());
}

MU_TEST(distance_two_points) {
    V2 v = V2(2, 1);
    V2 w = V2(1, 1);
    mu_assert_double_eq(w.dist(v), 1);
}

MU_TEST(plus_operator) {
    V2 v = V2();
    V2 w = V2(1, 1);
    V2 r = v + w;
    mu_assert_double_eq(r.x, w.x);
    mu_assert_double_eq(r.y, w.y);
}

MU_TEST(minus_operator) {
    V2 v = V2();
    V2 w = V2(1, 1);
    V2 r = v - w;
    mu_assert_double_eq(r.x, -w.x);
    mu_assert_double_eq(r.y, -w.y);
}

MU_TEST(plus_minus) {
    V2 v = V2();
    V2 w = V2(1, 1);
    V2 r = v + w - w;
    mu_assert_double_eq(r.x, 0);
    mu_assert_double_eq(r.y, 0);
}

MU_TEST(star_operator) {
    V2 v = V2(1, 2);
    V2 r = v * 2;
    mu_assert_double_eq(r.x, 2);
    mu_assert_double_eq(r.y, 4);
}

MU_TEST(slash_operator) {
    V2 v = V2(2, 4);
    V2 r = v / 2;
    mu_assert_double_eq(r.x, 1);
    mu_assert_double_eq(r.y, 2);
}

MU_TEST(star_slash) {
    V2 v = V2(1, 1);
    V2 r = v * 2 / 2;
    mu_assert_double_eq(r.x, 1);
    mu_assert_double_eq(r.y, 1);
}

MU_TEST_SUITE(v2_test) {
	MU_SUITE_CONFIGURE(NULL, NULL);

	MU_RUN_TEST(default_is_origin);
    MU_RUN_TEST(simple_add);
    MU_RUN_TEST(simple_sub);
    MU_RUN_TEST(add_sub);
    MU_RUN_TEST(simple_mul);
    MU_RUN_TEST(simple_div);
    MU_RUN_TEST(mul_div);
    MU_RUN_TEST(modulo_of_origin_is_zero);
    MU_RUN_TEST(simple_modulo);
    MU_RUN_TEST(dot_with_origin_is_zero);
    MU_RUN_TEST(normal_dot);
    MU_RUN_TEST(norm_of_origin_is_origin);
    MU_RUN_TEST(vector_norm);
    MU_RUN_TEST(normalized_vector_modulo_is_one);
    MU_RUN_TEST(distance_from_origin_is_vector_modulo);
    MU_RUN_TEST(distance_two_points);

    // operator
    MU_RUN_TEST(plus_operator);
    MU_RUN_TEST(minus_operator);
    MU_RUN_TEST(plus_minus);
    MU_RUN_TEST(star_operator);
    MU_RUN_TEST(slash_operator);
    MU_RUN_TEST(star_slash);
}

#endif // V2_TEST_HPP