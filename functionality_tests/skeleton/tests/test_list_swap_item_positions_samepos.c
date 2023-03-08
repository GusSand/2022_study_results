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

static void test_list_swap_item_positions_samepos(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 2.0, 1, 2), EXIT_SUCCESS);
    assert_int_equal(list_swap_item_positions(&head, 1, 1), EXIT_SUCCESS);
    // Swapping i for i should not change the list
    assert_string_equal(head->item_name, "item1");
    assert_string_equal(head->next->item_name, "item2");
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_swap_item_positions_samepos),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}