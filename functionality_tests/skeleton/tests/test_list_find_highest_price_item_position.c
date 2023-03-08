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

static void test_list_find_highest_price_item_position(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1.5", 5.0, 1, 3), EXIT_SUCCESS);
    int pos = 0;
    assert_int_equal(list_find_highest_price_item_position(head, &pos), EXIT_SUCCESS);
    assert_int_equal(pos, 3);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_find_highest_price_item_position),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
