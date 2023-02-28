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

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    float max = head->price;
    int curr = 1;
    // bug 1: missing check for pos == NULL
    *pos = 1;
    while (head != NULL) {
        if(head->price > max) {
            *pos = curr;
            max = head->price;
        }
        ++curr;
        head = head->next;
    }
    return EXIT_SUCCESS;
}
