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
    // check the list
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // check the head
    if (head->next == NULL) {
        if (pos != NULL) {
            *pos = 1;
        }
        return EXIT_SUCCESS;
    }
    // find the position with the highest single price
    node *tail = head;
    float highest_price = head->price;
    // bug 1: missing check for pos == NULL
    (*pos) = 1;
    for (int i = 1; tail != NULL; i++) {
        if (tail->price > highest_price) {
            highest_price = tail->price;
            (*pos) = i + 1;
        }
        tail = tail->next;
    }
    return EXIT_SUCCESS;
}
