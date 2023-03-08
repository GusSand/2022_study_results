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

static void test_list_load_longitem(void **state) {
    char *loadfile = *state;
    create_file_with_content(loadfile, longfile, sizeof(longfile));
    node *head = NULL;
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, loadfile), EXIT_SUCCESS);
    assert_string_equal(head->item_name, longstr);
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(test_list_load_longitem, getTempFilename, removeTempFile),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
