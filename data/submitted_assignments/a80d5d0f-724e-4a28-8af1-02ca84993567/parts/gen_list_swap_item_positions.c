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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (pos1 < 1 || pos2 < 1) {
        return EXIT_FAILURE;
    }
    // bug 1: missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    for (unsigned int i=1; i<pos1; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    ref_list_update_item_at_pos(head, curr->item_name, curr->price, curr->quantity, pos2);
    node *curr2 = *head;
    

    for (unsigned int i=1; i<pos2; i++) {
        if (curr2 == NULL) {
            return EXIT_FAILURE;
        }
        curr2 = curr2->next;
    }
    ref_list_update_item_at_pos(head, curr2->item_name, curr2->price, curr2->quantity, pos1);
    return EXIT_SUCCESS;
}
