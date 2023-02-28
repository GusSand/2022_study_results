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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    // bug 2: missing hceck for *head == NULL
    if (pos == 0) {
        (*head)->quantity = quantity;
        // bug 3: out of bounds write if new item_name is longer than old item_name
        // bug 4: possible improper NULL termination
        strncpy((*head)->item_name, item_name, MAX_ITEM_PRINT_LEN);
        (*head)->price = price;
        return EXIT_SUCCESS;
    }

    struct _node *curr = *head;
    int i = 0;

    while (curr != NULL && i < pos) {
        curr = curr->next;
        i++;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    else {
        curr->quantity = quantity;
        // bug 5: out of bounds write if new item_name is longer than old item_name
        // bug 6: possible improper NULL termination
        strncpy(curr->item_name, item_name, MAX_ITEM_PRINT_LEN);
        curr->price = price;
        return EXIT_SUCCESS;
    }
}
