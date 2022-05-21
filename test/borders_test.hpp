#ifndef BORDERS_TEST_HPP
#define BORDERS_TEST_HPP

#include "../lib/minunit.h"

#include "test_utils.hpp"

#include "../src/body.hpp"
#include "../src/borders.hpp"

#define test_template(initial, must_be, borders) MU__SAFE_BLOCK(\
        Body b = Body(initial, V2(0, 0), 1, 1);\
        borders sb = borders(10, 10);\
        sb.apply(&b);\
        assert_v2_eq(b.position, must_be);\
    )

#define test_template_solid(initial, must_be) test_template(initial, must_be, SolidBorders)

MU_TEST(no_changes_if_inside_solid) {
    test_template_solid(V2(1, 1), V2(1, 1));
}

MU_TEST(out_on_right_solid) {
    test_template_solid(V2(11, 1), V2(10, 1));
}

MU_TEST(out_on_left_solid) {
    test_template_solid(V2(-1, 1), V2(0, 1));
}

MU_TEST(out_on_top_solid) {
    test_template_solid(V2(1, -1), V2(1, 0));
}

MU_TEST(out_on_bottom_solid) {
    test_template_solid(V2(1, 11), V2(1, 10));
}

MU_TEST(bottom_right_corner_solid) {
    test_template_solid(V2(11, 11), V2(10, 10));
}

MU_TEST(top_left_corner_solid) {
    test_template_solid(V2(-1, -1), V2(0, 0));
}

MU_TEST_SUITE(borders_test) {
    MU_SUITE_CONFIGURE(NULL, NULL);

    MU_RUN_TEST(no_changes_if_inside_solid);
    MU_RUN_TEST(out_on_right_solid);
    MU_RUN_TEST(out_on_left_solid);
    MU_RUN_TEST(out_on_top_solid);
    MU_RUN_TEST(out_on_bottom_solid);
    MU_RUN_TEST(bottom_right_corner_solid);
    MU_RUN_TEST(top_left_corner_solid);
}

#endif // BORDERS_TEST_HPP