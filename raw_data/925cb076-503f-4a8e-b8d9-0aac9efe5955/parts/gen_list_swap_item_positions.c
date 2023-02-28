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
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for pos1 < 0
    // bug 2: missing check for head == NULL
    // bug 3: missing check for *head == NULL
    // bug 4: missing check for next == NULL
    while (pos1--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    *head = temp->next;

    // bug 5: missing check for pos2 < 0
    while (pos2--) {
        // bug 6: missing check for next == NULL
        head = &(*head)->next;
    }

    node* temp2 = *head;
    // bug 7: memory leak by overwriting *head
    *head = temp2->next;

    if (temp2->next == NULL) {
        temp2->next = temp;
    }
    else {
        temp2->next = temp->next;
    }

    temp->next = temp2;
    return EXIT_SUCCESS;
}
