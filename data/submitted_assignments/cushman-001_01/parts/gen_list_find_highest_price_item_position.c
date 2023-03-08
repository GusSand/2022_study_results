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
        printf("Error: list_find_highest_price_item_position\n");
        return EXIT_FAILURE;
    }
    node *curr = head;
    // bug 1: missing check for pos == NULL
    *pos = 0;
    float max = 0.0;
    while (curr!= NULL) {
        if (curr->price > max) {
            max = curr->price;
            *pos = *pos + 1;
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}
