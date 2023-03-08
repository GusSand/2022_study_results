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

static void test_list_init(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_null(head);
}

static void test_list_init_nullhead(void **state) {
    (void) state;
    assert_int_equal(list_init(NULL), EXIT_FAILURE);
}

static void test_list_add_item_at_pos(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 2.0, 1, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1.5", 1.5, 1, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item4", 4.0, 1, 4), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item1");
    assert_string_equal(head->next->item_name, "item1.5");
    assert_string_equal(head->next->next->item_name, "item2");
    assert_string_equal(head->next->next->next->item_name, "item4");
    assert_null(head->next->next->next->next);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_add_item_at_pos_nullhead(void **state) {
    (void) state;
    assert_int_equal(list_add_item_at_pos(NULL, "item1", 1.0, 1, 1), EXIT_FAILURE);
}

static void test_list_add_item_at_pos_nullitem(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, NULL, 1.0, 1, 1), EXIT_FAILURE);
}

static void test_list_add_item_at_pos_oob(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 0), EXIT_FAILURE);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, -1), EXIT_FAILURE);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 2), EXIT_FAILURE);
    assert_null(head);
}

static void test_list_item_to_string(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    char str[100];
    assert_int_equal(list_item_to_string(head, str), EXIT_SUCCESS);
    // "quantity * item_name @ $price ea"
    assert_string_equal(str, "1 * item1 @ $1.00 ea");
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_item_to_string_nullhead(void **state) {
    (void) state;
    char str[100];
    assert_int_equal(list_item_to_string(NULL, str), EXIT_FAILURE);
}

static void test_list_item_to_string_nullstr(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_item_to_string(head, NULL), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_item_to_string_longstr(void **state) {
    (void) state;
    char str[100];
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, longstr, 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_item_to_string(head, str), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_print(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "banana", 1.0, 3, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "orange", 2.0, 2, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "apple", 3.0, 4, 3), EXIT_SUCCESS);
    expect_function_call_any(test_printf);
	assert_int_equal(list_print(head), EXIT_SUCCESS);
    char *expected_output = \
        "1: 3 * banana @ $1.00 ea\n" \
        "2: 2 * orange @ $2.00 ea\n" \
        "3: 4 * apple @ $3.00 ea\n";
    assert_string_equal(big_buffer, expected_output);
    memset(big_buffer, 0, sizeof(big_buffer));
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_print_nullhead(void **state) {
    (void) state;
    assert_int_equal(list_print(NULL), EXIT_FAILURE);
}

static void test_list_print_longitem(void **state) {
    (void) state;
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, longstr, 1.0, 3, 1), EXIT_SUCCESS);
    ignore_function_calls(test_printf);
	assert_int_equal(list_print(head), EXIT_FAILURE);
    memset(big_buffer, 0, sizeof(big_buffer));
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_update_item_at_pos(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    char *newname = "apple";
    assert_int_equal(list_update_item_at_pos(&head, newname, 3.0, 2, 1), EXIT_SUCCESS);
    assert_string_equal(head->item_name, newname);
    assert_float_equal(head->price, 3.0, 0.01);
    assert_int_equal(head->quantity, 2);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_update_item_at_pos_nullhead(void **state) {
    (void) state;
    char *newname = "foo";
    assert_int_equal(list_update_item_at_pos(NULL, newname, 3.0, 2, 1), EXIT_FAILURE);
}

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

static void test_list_update_item_at_pos_oob(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    char *newname = "foo";
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_update_item_at_pos(&head, newname, 3.0, 2, 0), EXIT_FAILURE);
    assert_int_equal(list_update_item_at_pos(&head, newname, 3.0, 2, -1), EXIT_FAILURE);
    assert_int_equal(list_update_item_at_pos(&head, newname, 3.0, 2, 2), EXIT_FAILURE);
    // Failed updates should not change the item
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_remove_item_at_pos(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 2.0, 2, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item3", 3.0, 3, 3), EXIT_SUCCESS);
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

static void test_list_remove_item_at_pos_nullhead(void **state) {
    (void) state;
    assert_int_equal(list_remove_item_at_pos(NULL, 1), EXIT_FAILURE);
}

static void test_list_remove_item_at_pos_oob(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_remove_item_at_pos(&head, 0), EXIT_FAILURE);
    assert_int_equal(list_remove_item_at_pos(&head, -1), EXIT_FAILURE);
    assert_int_equal(list_remove_item_at_pos(&head, 2), EXIT_FAILURE);
    assert_non_null(head);
    // Failed remove should not change the list
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_swap_item_positions(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 2.0, 2, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item3", 3.0, 3, 3), EXIT_SUCCESS);
    assert_int_equal(list_swap_item_positions(&head, 1, 2), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item2");
    assert_string_equal(head->next->item_name, "item1");
    assert_string_equal(head->next->next->item_name, "item3");
    assert_int_equal(list_swap_item_positions(&head, 2, 3), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item2");
    assert_string_equal(head->next->item_name, "item3");
    assert_string_equal(head->next->next->item_name, "item1");
    assert_int_equal(list_swap_item_positions(&head, 3, 1), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item1");
    assert_string_equal(head->next->item_name, "item3");
    assert_string_equal(head->next->next->item_name, "item2");
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

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

static void test_list_swap_item_positions_nullhead(void **state) {
    (void) state;
    assert_int_equal(list_swap_item_positions(NULL, 1, 2), EXIT_FAILURE);
}

static void test_list_swap_item_positions_oob(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 2.0, 1, 2), EXIT_SUCCESS);
    assert_int_equal(list_swap_item_positions(&head, 0, 2), EXIT_FAILURE);
    assert_int_equal(list_swap_item_positions(&head, -1, 2), EXIT_FAILURE);
    assert_int_equal(list_swap_item_positions(&head, 3, 2), EXIT_FAILURE);
    assert_int_equal(list_swap_item_positions(&head, 1, 0), EXIT_FAILURE);
    assert_int_equal(list_swap_item_positions(&head, 1, -1), EXIT_FAILURE);
    assert_int_equal(list_swap_item_positions(&head, 1, 3), EXIT_FAILURE);
    // Failed swap should not change the list
    assert_string_equal(head->item_name, "item1");
    assert_string_equal(head->next->item_name, "item2");
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

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

static void test_list_find_highest_price_item_position_nullhead(void **state) {
    (void) state;
    int pos = 0;
    assert_int_equal(list_find_highest_price_item_position(NULL, &pos), EXIT_FAILURE);
}

static void test_list_find_highest_price_item_position_nullpos(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_find_highest_price_item_position(head, NULL), EXIT_FAILURE);
}

static void test_list_cost_sum(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1.5", 5.0, 1, 3), EXIT_SUCCESS);
    float total = 0.0;
    assert_int_equal(list_cost_sum(head, &total), EXIT_SUCCESS);
    assert_float_equal(total, 16.0, 0.01);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_cost_sum_nullhead(void **state) {
    (void) state;
    float total = 0.0;
    assert_int_equal(list_cost_sum(NULL, &total), EXIT_FAILURE);
}

static void test_list_cost_sum_nulltotal(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1.5", 5.0, 1, 3), EXIT_SUCCESS);
    assert_int_equal(list_cost_sum(head, NULL), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_save(void **state) {
    char *filename = *state;
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1.5", 5.0, 1, 3), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, longstr, 1.0, 1, 4), EXIT_SUCCESS);
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
    char bigline[768];
    char expected[768];
    strcpy(expected, longstr);
    strcat(expected, ",1.00,1\n");
    r = fgets(bigline, 768, fp);
    assert_non_null(r);
    assert_string_equal(bigline, expected);
    r = fgets(line, 100, fp);
    assert_null(r);
    fclose(fp);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_save_nullhead(void **state) {
    char *filename = *state;
    assert_int_equal(list_save(NULL, filename), EXIT_FAILURE);
}

static void test_list_save_nullfilename(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_save(head, NULL), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_save_badfile(void **state) {
    char *filename = *state;
    // Create an empty file and make it unwritable
    FILE *fp = fopen(filename, "w");
    assert_non_null(fp);
    assert_int_equal(fclose(fp), 0);
    assert_int_equal(chmod(filename, 0), 0);
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_save(head, filename), EXIT_FAILURE);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

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

static void test_list_load_nullhead(void **state) {
    (void) state;
    char *loadfile = "example_load_file.txt";
    assert_int_equal(list_load(NULL, loadfile), EXIT_FAILURE);
}

static void test_list_load_nullfilename(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_load(&head, NULL), EXIT_FAILURE);
}

static void test_list_load_longitem(void **state) {
    char *loadfile = *state;
    create_file_with_content(loadfile, longfile, sizeof(longfile));
    node *head = NULL;
    char longstr[512];
    memset(longstr, 'a', sizeof(longstr));
    longstr[sizeof(longstr) - 1] = '\0';
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, loadfile), EXIT_SUCCESS);
    assert_string_equal(head->item_name, longstr);
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_load_badparse(void **state) {
    char *loadfile = *state;
    create_file_with_content(loadfile, badfile, sizeof(badfile));
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, loadfile), EXIT_FAILURE);
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_null(head->next);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_load_badfile(void **state) {
    char *filename = *state;
    // Create an empty file and make it unreadable
    FILE *fp = fopen(filename, "w");
    assert_non_null(fp);
    assert_int_equal(fclose(fp), 0);
    assert_int_equal(chmod(filename, 0), 0);
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, filename), EXIT_FAILURE);
}

static void test_list_load_missingfile(void **state) {
    // Random name to avoid collisions
    char *filename = "999704d1-e089-4030-b2d4-ae4c211cccc1";
    // Create an empty file and make it unreadable
    FILE *fp = fopen(filename, "r");
    assert_null(fp);
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_load(&head, filename), EXIT_FAILURE);
}

static void test_list_deduplicate(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 10, 2), EXIT_SUCCESS);
    assert_int_equal(list_deduplicate(&head), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 11);
    assert_null(head->next);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_deduplicate_nullhead(void **state) {
    (void) state;
    assert_int_equal(list_deduplicate(NULL), EXIT_FAILURE);
}

static void test_list_deduplicate_single(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_deduplicate(&head), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_null(head->next);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

static void test_list_deduplicate_nodups(void **state) {
    (void) state;
    node *head = NULL;
    assert_int_equal(list_init(&head), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item1", 1.0, 1, 1), EXIT_SUCCESS);
    assert_int_equal(list_add_item_at_pos(&head, "item2", 2.0, 2, 2), EXIT_SUCCESS);
    assert_int_equal(list_deduplicate(&head), EXIT_SUCCESS);
    assert_string_equal(head->item_name, "item1");
    assert_float_equal(head->price, 1.0, 0.01);
    assert_int_equal(head->quantity, 1);
    assert_string_equal(head->next->item_name, "item2");
    assert_float_equal(head->next->price, 2.0, 0.01);
    assert_int_equal(head->next->quantity, 2);
    assert_null(head->next->next);
    assert_int_equal(list_free(&head), EXIT_SUCCESS);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_list_init),
        cmocka_unit_test(test_list_init_nullhead),
        cmocka_unit_test(test_list_item_to_string),
        cmocka_unit_test(test_list_item_to_string_nullhead),
        cmocka_unit_test(test_list_item_to_string_nullstr),
        cmocka_unit_test(test_list_item_to_string_longstr),
        cmocka_unit_test(test_list_print),
        cmocka_unit_test(test_list_print_nullhead),
        cmocka_unit_test(test_list_print_longitem),
        cmocka_unit_test(test_list_add_item_at_pos),
        cmocka_unit_test(test_list_add_item_at_pos_nullhead),
        cmocka_unit_test(test_list_add_item_at_pos_nullitem),
        cmocka_unit_test(test_list_add_item_at_pos_oob),
        cmocka_unit_test(test_list_update_item_at_pos),
        cmocka_unit_test(test_list_update_item_at_pos_nullhead),
        cmocka_unit_test(test_list_update_item_at_pos_nullstr),
        cmocka_unit_test(test_list_update_item_at_pos_oob),
        cmocka_unit_test(test_list_remove_item_at_pos),
        cmocka_unit_test(test_list_remove_item_at_pos_nullhead),
        cmocka_unit_test(test_list_remove_item_at_pos_oob),
        cmocka_unit_test(test_list_swap_item_positions),
        cmocka_unit_test(test_list_swap_item_positions_nullhead),
        cmocka_unit_test(test_list_swap_item_positions_samepos),
        cmocka_unit_test(test_list_swap_item_positions_oob),
        cmocka_unit_test(test_list_find_highest_price_item_position),
        cmocka_unit_test(test_list_find_highest_price_item_position_nullhead),
        cmocka_unit_test(test_list_find_highest_price_item_position_nullpos),
        cmocka_unit_test(test_list_cost_sum),
        cmocka_unit_test(test_list_cost_sum_nullhead),
        cmocka_unit_test(test_list_cost_sum_nulltotal),
        cmocka_unit_test_setup_teardown(test_list_save, getTempFilename, removeTempFile),
        cmocka_unit_test_setup_teardown(test_list_save_badfile, getTempFilename, removeTempFile),
        cmocka_unit_test(test_list_save_nullhead),
        cmocka_unit_test(test_list_save_nullfilename),
        cmocka_unit_test_setup_teardown(test_list_load, getTempFilename, removeTempFile),
        cmocka_unit_test_setup_teardown(test_list_load_longitem, getTempFilename, removeTempFile),
        cmocka_unit_test_setup_teardown(test_list_load_badparse, getTempFilename, removeTempFile),
        cmocka_unit_test_setup_teardown(test_list_load_badfile, getTempFilename, removeTempFile),
        cmocka_unit_test(test_list_load_nullhead),
        cmocka_unit_test(test_list_load_nullfilename),
        cmocka_unit_test(test_list_load_missingfile),
        cmocka_unit_test(test_list_deduplicate),
        cmocka_unit_test(test_list_deduplicate_nullhead),
        cmocka_unit_test(test_list_deduplicate_single),
        cmocka_unit_test(test_list_deduplicate_nodups),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
