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

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS

#include "reflist.h"
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    // check the list
    // bug 1: missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // check the pos
    if (pos == 0) {
        return EXIT_FAILURE;
    }
    // if the pos is 1, remove the head
    if (pos == 1) {
        node *temp = (*head)->next;
        free((*head)->item_name);
        free(*head);
        *head = temp;
        return EXIT_SUCCESS;
    }
    // else, remove the tail
    node *tail = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (tail->next == NULL) {
            return EXIT_FAILURE;
        }
        tail = tail->next;
    }
    // bug 2: missing check for next == NULL
    node *temp = tail->next->next;
    free(tail->next->item_name);
    free(tail->next);
    tail->next = temp;
    return EXIT_SUCCESS;
}
