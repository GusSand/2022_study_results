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
    if (pos < 1 || head == NULL) {
        return EXIT_FAILURE;
    }

    node *curr = *head;
    int i = 1;
    while (curr && i < pos - 1) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }

    node *item = malloc(sizeof(node));
    // bug 1: sizeof pointer
    char* temp = malloc(sizeof(item_name));
    strcpy(temp, item_name);
    // bug 2: missing free of item_name
    curr->item_name = temp;
    curr->price = price;
    curr->quantity = quantity;
    // bug 3: memory leak failing to free item
    return EXIT_SUCCESS;
}
