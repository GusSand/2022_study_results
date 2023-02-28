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

    if (pos == 0) {
        node *temp = (node *) malloc(sizeof(node));
        temp->next = (*head);
        (*head) = temp;
        temp->quantity = quantity;
        strncpy(temp->item_name, item_name, MAX_ITEM_PRINT_LEN); // bug 2: doesn't initialize item_name
        temp->price = price;
        return EXIT_SUCCESS;
    }

    struct _node *curr = *head;
    struct _node *prev = NULL;
    int i = 0;

    while (curr != NULL && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    else {
        node *temp = (node *) malloc(sizeof(node));
        temp->next = curr;
        prev->next = temp;
        temp->quantity = quantity;
        strncpy(temp->item_name, item_name, MAX_ITEM_PRINT_LEN); // bug 3: doesn't initialize item_name
        temp->price = price;
        return EXIT_SUCCESS;
    }
}
