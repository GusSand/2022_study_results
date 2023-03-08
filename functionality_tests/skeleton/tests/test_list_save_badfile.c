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

static void test_list_save_badfile(void **state) {
    char *filename = *state;
    // Create an empty file and make it unwritable
    FILE *fp = fopen(filename, "w");
    assert_non_null(fp);
    assert_int_equal(fclose(fp), 0);
    assert_int_equal(chmod(filename, 0), 0);
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_save(head, filename), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(test_list_save_badfile, getTempFilename, removeTempFile),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
