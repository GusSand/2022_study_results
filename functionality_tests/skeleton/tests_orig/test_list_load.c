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

static void test_list_load(void **state) {
    (void) state;
    char *loadfile = "example_load_file.txt";
    node *head = NULL;
    assert_int_equal(list_load(&head, loadfile), EXIT_SUCCESS);
    // Expected list contents:
    // apple,0.80,2
    // banana,0.50,3
    // cheese,10.59,1
    assert_string_equal(head->item_name, "apple");
    assert_float_equal(head->price, 0.80, 0.01);
    assert_int_equal(head->quantity, 2);
    assert_string_equal(head->next->item_name, "banana");
    assert_float_equal(head->next->price, 0.50, 0.01);
    assert_int_equal(head->next->quantity, 3);
    assert_string_equal(head->next->next->item_name, "cheese");
    assert_float_equal(head->next->next->price, 10.59, 0.01);
    assert_int_equal(head->next->next->quantity, 1);
    assert_null(head->next->next->next);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_list_load),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
