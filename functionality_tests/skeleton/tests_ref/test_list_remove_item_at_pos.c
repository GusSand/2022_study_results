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

static void test_list_remove_item_at_pos(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(ref_list_init(&head), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item2", 2.0, 2, 2), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item3", 3.0, 3, 3), EXIT_SUCCESS);
    // Remove item3 in position 3
    assert_int_equal(list_remove_item_at_pos(&head, 3), EXIT_SUCCESS);
    assert_null(head->next->next);
    // Remove item1 in position 1
    assert_int_equal(list_remove_item_at_pos(&head, 1), EXIT_SUCCESS);
    assert_null(head->next);
    // item2 should now be in position 1
    assert_string_equal(head->item_name, "item2");
    // Remove item2 in position 1
    assert_int_equal(list_remove_item_at_pos(&head, 1), EXIT_SUCCESS);
    assert_null(head);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_remove_item_at_pos),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
