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
    if ((head == NULL) || (*head == NULL)){
        return EXIT_FAILURE;
    }
    node *current = *head;
    int i = 1;
    while (i < pos && current != NULL){
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: missing free
    // bug 2: missing strdup
    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;
    return EXIT_SUCCESS;
}
