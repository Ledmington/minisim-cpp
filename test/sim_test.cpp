#include "../lib/minunit.h"

#include "simulation_test.hpp"
#include "body_test.hpp"

int main(int argc, char *argv[]) {
    MU_RUN_SUITE(body_test);
	MU_RUN_SUITE(simulation_test);
	MU_REPORT();
	return MU_EXIT_CODE;
}
