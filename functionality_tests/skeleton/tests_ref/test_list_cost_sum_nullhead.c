#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

// No unistd.h on clang for Windows?
#ifndef _WIN32
#include <unistd.h>
#endif

#include <string.h>
#include <stdint.h>
#include <signal.h>
#include "list.h"
#include "cmocka.h"
#include "test_common.h"

static void test_list_cost_sum_nullhead(void **state) {
    (void) state;
    float total = 0.0;
    assert_int_equal(list_cost_sum(NULL, &total), EXIT_FAILURE);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_cost_sum_nullhead),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
