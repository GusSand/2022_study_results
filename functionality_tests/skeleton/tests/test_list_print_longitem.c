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

static void test_list_print_longitem(void **state) {
    (void) state;
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, longstr, 1.0, 3, 1), EXIT_SUCCESS);
    ignore_function_calls(test_printf);
	assert_int_equal(list_print(head), EXIT_FAILURE);
    memset(big_buffer, 0, sizeof(big_buffer));
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_print_longitem),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
