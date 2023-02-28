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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // if the list is empty, return fail
    // bug 1: missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // if the node to be removed is at position 1, set the head->next to be the head
    if (pos == 1) {
        node *new_head = (*head)->next;
        free(*head);
        // bug 2: missing free of item_name
        *head = new_head;
        return EXIT_SUCCESS;
    }
    // else, find the node that is at position pos-
    node *cur = *head;
    int i = 1;
    while (cur != NULL && i < pos) {
        cur = cur->next;
        i++;
    }
    if (i < pos) {
        return EXIT_FAILURE;
    }
    node *prev = *head;
    while (prev->next != cur) {
        prev = prev->next;
    }
    prev->next = cur->next;
    // free the curr node
    // free(cur);
    // bug 3: missing free of item
    // bug 4: missing free of item_name
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
