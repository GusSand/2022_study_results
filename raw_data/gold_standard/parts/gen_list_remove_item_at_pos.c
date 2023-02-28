#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
// helper. if previous is non-null, it will be set to point to the item at pos-1
static node* find_node_at_pos(node *head, unsigned int pos, node **previous) {
    if (head == NULL) {
        return NULL;
    }
    int i = 1;
    node *curr = NULL;
    node *prev = NULL;
    for (curr = head; curr != NULL && i < pos; curr = curr->next, i++) {
        prev = curr;
        // do nothing
    }
    if (i == pos) {
        if (previous) *previous = prev;
        return curr;
    }
    else {
        if (previous) *previous = NULL;
        return NULL;
    }
}
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *prev = NULL;
    node *to_delete = find_node_at_pos(*head, pos, &prev);
    if (to_delete == NULL) {
        return EXIT_FAILURE;
    }
    if (prev == NULL) {
        *head = to_delete->next;
    } else {
        prev->next = to_delete->next;
    }
    free(to_delete->item_name);
    free(to_delete);
    return EXIT_SUCCESS;
}
