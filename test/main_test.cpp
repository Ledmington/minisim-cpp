#include "../lib/minunit.h"

#include "simulation_test.hpp"
#include "body_test.hpp"
#include "v2_test.hpp"

int main(int argc, char *argv[]) {
	printf("a");
	MU_RUN_SUITE(v2_test);
	printf("b");
    MU_RUN_SUITE(body_test);
	printf("d");
	MU_RUN_SUITE(simulation_test);
	MU_REPORT();
	return MU_EXIT_CODE;
}
