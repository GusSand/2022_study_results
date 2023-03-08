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
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: missing check for head == NULL
    // Iterate to the correct position
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    while (curr_node != NULL && curr_pos < pos)
    {
        curr_node = curr_node->next;
        curr_pos++;
    }

    if (curr_node == NULL)
    {
        printf("ERROR: Item not found\n");
        return EXIT_FAILURE;
    }

    // Update the item
    // bug 2: missing free
    // bug 3: missing strdup
    curr_node->item_name = item_name;
    curr_node->price = price;
    curr_node->quantity = quantity;

    return EXIT_SUCCESS;
}
