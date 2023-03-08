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

static void test_list_load_missingfile(void **state) {
    // Random name to avoid collisions
    char *filename = "999704d1-e089-4030-b2d4-ae4c211cccc1";
    // Create an empty file and make it unreadable
    FILE *fp = fopen(filename, "r");
    assert_null(fp);
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, filename), EXIT_FAILURE);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_load_missingfile),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
