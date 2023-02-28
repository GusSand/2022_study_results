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
    node *curr = *head;
    if (curr == NULL){
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        curr->quantity = quantity;
        curr->price = price;
        // bug 2: missing free
        // bug 3: missing strdup
        curr->item_name = item_name;
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
    curr->quantity = quantity;
    curr->price = price;
    // bug 4: missing free
    // bug 5: missing strdup
    curr->item_name = item_name;
    return EXIT_SUCCESS;
}
