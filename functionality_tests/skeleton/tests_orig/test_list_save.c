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

static void test_list_save(void **state) {
    char *filename = *state;
    node *head = NULL;
    assert_int_equal(ref_list_init(&head), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item2", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(ref_list_add_item_at_pos(&head, "item1.5", 5.0, 1, 3), EXIT_SUCCESS);
    assert_int_equal(list_save(head, filename), EXIT_SUCCESS);
    FILE *fp = fopen(filename, "r");
    assert_non_null(fp);
    // Format: item_name,price,quantity\n
    char line[100];
    char *r = NULL;
    r = fgets(line, 100, fp);
    assert_non_null(r);
    assert_string_equal(line, "item1,1.00,1\n");
    r = fgets(line, 100, fp);
    assert_non_null(r);
    assert_string_equal(line, "item2,1.00,10\n");
    r = fgets(line, 100, fp);
    assert_non_null(r);
    assert_string_equal(line, "item1.5,5.00,1\n");
    r = fgets(line, 100, fp);
    assert_null(r);
    fclose(fp);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_list_save, getTempFilename, removeTempFile),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
