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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: missing check for head == NULL

    // pos must be an integer >= 1
    if (pos < 1) {
        return EXIT_FAILURE;
    }

    node* prev_ptr = NULL;
    node* next_ptr = *head; // node that will be pushed down 1 index (curr node at pos)

    int counter = 1;
    while(counter < pos && next_ptr != NULL) {
        prev_ptr = next_ptr;
        next_ptr = next_ptr->next;
        counter++;
    }

    // counter should be equal to pos by end of while loop
    // otherwise this means we've looped until end of list and 
    // pos exceeds list length
    if (counter != pos) {
        return EXIT_FAILURE;
    }
    

    // make new node
    node* new_item_ptr = malloc(sizeof(node));
    // bug 2: missing check for item_name == NULL
    new_item_ptr->item_name = malloc(strlen(item_name) + 1);
    strcpy(new_item_ptr->item_name, item_name);
    new_item_ptr->price = price;
    new_item_ptr->quantity = quantity;
    new_item_ptr->next = next_ptr;

    // case: pos is not 1, hence prev_str != NULL
    if (pos != 1) {
        prev_ptr->next = new_item_ptr;
    } else {
        *head = new_item_ptr; // update head ptr if pos == 1
    }

    return EXIT_SUCCESS;
}
