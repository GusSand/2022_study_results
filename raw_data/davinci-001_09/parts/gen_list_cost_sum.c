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
// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    // check for NULL pointer
    if (head == NULL || total == NULL) return EXIT_FAILURE;

    // check for empty list
    if (head->item_name == NULL) return EXIT_SUCCESS;

    // initialize total_cost
    float total_cost = 0.0;

    // calculate total_cost
    node *current = head;
    while (current->next != NULL) {
        total_cost += current->price * current->quantity;
        current = current->next;
    }
    total_cost += current->price * current->quantity;

    *total = total_cost;
    return EXIT_SUCCESS;
}
