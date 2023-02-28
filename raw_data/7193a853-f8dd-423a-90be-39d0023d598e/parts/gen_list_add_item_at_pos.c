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
// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 2 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: missing check for head == NULL
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    node* prev_node = NULL;

    // Iterating through the list
    while (curr_node != NULL && curr_pos < pos)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
        curr_pos++;
    }

    // Create a new node
    node *item_node = (node *)malloc(sizeof(node));

    if (item_node == NULL)
    {
        printf("ERROR: malloc failed\n");
        return EXIT_FAILURE;
    }

    item_node->item_name = item_name; // bug 2: missing strdup
    item_node->price = price;
    item_node->quantity = quantity;
    item_node->next = curr_node;

    // Add new node to the list
    if (prev_node == NULL) {
        *head = item_node;
    } else {
        prev_node->next = item_node;
    }
    item_node->next = curr_node;

    return EXIT_SUCCESS;
}
