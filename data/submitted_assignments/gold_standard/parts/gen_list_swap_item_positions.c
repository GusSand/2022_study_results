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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    
    node *prev = NULL;
    node *curr = find_node_at_pos(*head, pos1, &prev);
    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    node *prev2 = NULL;
    node *curr2 = find_node_at_pos(*head, pos2, &prev2);
    if (curr2 == NULL) {
        return EXIT_FAILURE;
    }
    // Early exit if items to swap are the same
    if (curr == curr2) return EXIT_SUCCESS;
    
    // Swap
    if (prev == NULL) {
        *head = curr2;
    } else {
        prev->next = curr2;
    }
    if (prev2 == NULL) {
        *head = curr;
    } else {
        prev2->next = curr;
    }
    node *temp = curr->next;
    curr->next = curr2->next;
    curr2->next = temp;

    return EXIT_SUCCESS;
}
