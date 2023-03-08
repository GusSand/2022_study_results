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
    node *curr = *head;
    if (curr == NULL && pos == 1) {
        curr = malloc(sizeof(node));
        curr->item_name = item_name; // bug 2: missing strdup
        curr->price = price;
        curr->quantity = quantity;
        curr->next = NULL;
        *head = curr;
        return EXIT_SUCCESS;
    }
    if (curr == NULL && pos != 1) {
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        *head = malloc(sizeof(node));
        if (*head == NULL) {
            return EXIT_FAILURE;
        }
        (*head)->quantity = quantity;
        (*head)->price = price;
        (*head)->item_name = item_name; // bug 3: missing strdup
        (*head)->next = curr;
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (curr->next == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
        pos_count++;
    }
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return EXIT_FAILURE;
    }
    new_node->quantity = quantity;
    new_node->price = price;
    new_node->item_name = item_name; // bug 4: missing strdup
    new_node->next = curr->next;
    curr->next = new_node;
    return EXIT_SUCCESS;
}
