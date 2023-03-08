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

static void test_list_update_item_at_pos_nullstr(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_update_item_at_pos(&head, NULL, 3.0, 2, 1), EXIT_FAILURE);
    // Failed update should not change the item
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_update_item_at_pos_nullstr),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
