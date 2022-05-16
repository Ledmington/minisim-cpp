#ifndef SIM_BUILDER_TEST_HPP
#define SIM_BUILDER_TEST_HPP

#include "../lib/minunit.h"

#include "../src/simulation.hpp"
#include "../src/simulation_builder.hpp"

MU_TEST(builder_single_use) {
    SimulationBuilder sb = SimulationBuilder();
    sb.build();
    sb.build();
}

MU_TEST_SUITE(sim_builder_test){
    MU_SUITE_CONFIGURE(NULL, NULL);

    MU_RUN_TEST(builder_single_use);
}

#endif // SIM_BUILDER_TEST_HPP