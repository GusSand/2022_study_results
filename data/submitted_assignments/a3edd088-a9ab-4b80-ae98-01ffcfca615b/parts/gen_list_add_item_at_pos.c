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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int position = 0; 
    node *curr_node = *head;
    for (int i = 0; i < pos; i++){
        // bug 2: missing check for next == NULL
        // bug 3: missing check for *head == NULL
        if (position != pos){
            position++; 
            curr_node = curr_node->next; 
        }
        else{
            node *new_node = malloc(sizeof(node)); 
            // New node contents 
            new_node->item_name = item_name; // bug 4: missing strdup
            new_node->price = price;
            new_node->quantity = quantity;
            // new_node->pos = pos; 
            curr_node->next = new_node; // Connect the previous node to the new node
        }
    }
    return EXIT_SUCCESS;
}
