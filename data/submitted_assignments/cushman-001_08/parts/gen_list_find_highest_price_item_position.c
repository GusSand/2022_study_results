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
    node *curr;
    int i, highest_price_pos = 0;
    float highest_price = 0;
    
    // check for invalid inputs
    if (head == NULL || pos == NULL) return EXIT_FAILURE;
    
    // check if the list is empty
    if (head == NULL) return EXIT_FAILURE;
    
    curr = head;
    for (i = 0; curr != NULL; curr = curr->next, i++) {
        if (curr->price > highest_price) {
            highest_price = curr->price;
            highest_price_pos = i;
        }
    }
    
    *pos = highest_price_pos;
    return EXIT_SUCCESS;
}
