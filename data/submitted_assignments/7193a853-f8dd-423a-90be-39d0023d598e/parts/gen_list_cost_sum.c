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
// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    float sum = 0;
    
    // Iterate through the list
    node* curr_node = head;

    while(curr_node != NULL){
        float item_price = curr_node->price;
        int item_quantity = curr_node->quantity;

        sum += item_price*item_quantity;
        curr_node = curr_node->next;
    }

    // Updating total
    // bug 1: missing check for total == NULL
    *total = sum;

    return EXIT_SUCCESS;
}
