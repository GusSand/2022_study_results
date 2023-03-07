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
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        int curr_pos  = 1 ; 
        // bug 1: int vs float confusion
        int max = -1; 
        while (cur != NULL) {
            if (cur->price > max) {
                max = cur->price; 
                // bug 2: int* vs int confusion
                pos = curr_pos; 
                }
            cur = cur->next;
            curr_pos++;
        }
    }
    return EXIT_SUCCESS;
    
}
