#include "../lib/minunit.h"

#include "simulation_test.hpp"
#include "body_test.hpp"
#include "v2_test.hpp"
#include "sim_builder_test.hpp"
#include "borders_test.hpp"

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(v2_test);
    MU_RUN_SUITE(body_test);
	MU_RUN_SUITE(borders_test);
	MU_RUN_SUITE(sim_builder_test);
	MU_RUN_SUITE(simulation_test);
	MU_REPORT();
	return MU_EXIT_CODE;
}
