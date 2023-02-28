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
    // if the list is empty, reutrn failure
    // bug 1: missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    node *cur = *head;
    int i = 1;
    while (cur != NULL && i < pos) {
        cur = cur->next;
        i++;
    }
    if (i < pos) {
        return EXIT_FAILURE;
    }
    cur->price = price;
    cur->quantity = quantity;
    // bug 2: missing free
    // free(cur->item_name);
    cur->item_name = strdup(item_name);
    // cur->item_name = item_name;
    return EXIT_SUCCESS;
}
