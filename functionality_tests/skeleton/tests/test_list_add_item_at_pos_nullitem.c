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

static void test_list_add_item_at_pos_nullitem(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, NULL, 1.0, 1, 1), EXIT_FAILURE);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_add_item_at_pos_nullitem),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
