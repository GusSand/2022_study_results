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
node* get_item_at_pos(node** head, int pos) {
    // bug 1: missing check for head == NULL
    node* curr = *head;
    int i = 1;
    while (curr != NULL) {
        if (i == pos) {
            return curr;
        }
        curr = curr->next;
        i++;
    }
    return NULL;
}
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node* item1 = get_item_at_pos(head, pos1);
    node* item2 = get_item_at_pos(head, pos2);
    if (item1 == NULL || item2 == NULL) {
        return EXIT_FAILURE;
    }

    char* temp_item_name = item1->item_name;
    item1->item_name = item2->item_name;
    item2->item_name = temp_item_name;

    float temp_price = item1->price;
    item1->price = item2->price;
    item2->price = temp_price;

    int temp_quantity = item1->quantity;
    item1->quantity = item2->quantity;
    item2->quantity = temp_quantity;

    return EXIT_SUCCESS;
}
