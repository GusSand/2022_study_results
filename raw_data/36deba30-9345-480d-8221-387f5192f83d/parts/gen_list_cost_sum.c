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
// calculate the total cost of the list (sum of all prices * quantity)
int list_cost_sum(node *head, float *total){
    // TODO: Implement this
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = head;
    float sum = 0;
    while (curr != NULL){
        sum += curr->price * curr->quantity;
        curr = curr->next;
    }
    // bug 1: missing check for total == NULL
    *total = sum;
    return EXIT_SUCCESS;
}
