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

static void test_list_item_to_string_longstr(void **state) {
    (void) state;
    char str[100];
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    node *head = NULL;
    assert_int_equal(ref_list_init(&head), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, longstr, 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_item_to_string(head, str), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_item_to_string_longstr),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
