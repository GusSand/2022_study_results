#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>

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

static void test_list_deduplicate(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(ref_list_init(&head), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item1", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(list_deduplicate(&head), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 11);
    assert_null(head->next);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_list_deduplicate),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
