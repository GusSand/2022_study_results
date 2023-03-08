#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"

#ifdef UNIT_TESTING
/* Redirect printf to a function in the test application so it's possible to
 * test the standard output. You can ignore this; it's not relevant to the
 * assignment. */
#ifdef printf
#undef printf
#endif /* printf */
extern int test_printf(const char *format, ...);
#define printf test_printf
#endif

#define MAX_ITEM_PRINT_LEN 100

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS

#include "reflist.h"
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        *pos = 0;
        return EXIT_FAILURE;
    }
    *pos = 1;
    int cur_pos = 1;
    float max_price = head->price;
    node *cur = head->next;
    while (cur) {
        if (cur->price > max_price) {
            *pos = cur_pos+1;
            max_price = cur->price;
        }
        cur = cur->next;
        cur_pos++;
    }
    return EXIT_SUCCESS;
}
