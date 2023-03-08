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

static void test_list_print(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "banana", 1.0, 3, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "orange", 2.0, 2, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "apple", 3.0, 4, 3), EXIT_SUCCESS);
    expect_function_call_any(test_printf);
	assert_int_equal(list_print(head), EXIT_SUCCESS);
    char *expected_output = \
        "1: 3 * banana @ $1.00 ea\n" \
        "2: 2 * orange @ $2.00 ea\n" \
        "3: 4 * apple @ $3.00 ea\n";
    assert_string_equal(big_buffer, expected_output);
    memset(big_buffer, 0, sizeof(big_buffer));
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_print),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
