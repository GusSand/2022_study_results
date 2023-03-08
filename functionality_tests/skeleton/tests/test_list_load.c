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

static void test_list_load(void **state) {
    char *filename = *state;
    create_file_with_content(filename, goodfile, sizeof(goodfile));
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, filename), EXIT_SUCCESS);
    // Expected list contents:
    // item1,1.0,1
    // apple,0.80,2
    // banana,0.50,3
    // cheese,10.59,1
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_string_equal(head->next->item_name, "apple");
    assert_float_equal(head->next->price, 0.80, 0.01);
    assert_int_equal(head->next->quantity, 2);
    assert_string_equal(head->next->next->item_name, "banana");
    assert_float_equal(head->next->next->price, 0.50, 0.01);
    assert_int_equal(head->next->next->quantity, 3);
    assert_string_equal(head->next->next->next->item_name, "cheese");
    assert_float_equal(head->next->next->next->price, 10.59, 0.01);
    assert_int_equal(head->next->next->next->quantity, 1);
    assert_null(head->next->next->next->next);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test_setup_teardown(test_list_load, getTempFilename, removeTempFile),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
