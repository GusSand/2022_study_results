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
    if (pos == 1) {
        node *curr = *head;
        *head = curr->next;
        free(curr->item_name);
        free(curr);
        return EXIT_SUCCESS;
    }
    node *prev = *head;
    node *curr = *head;
    while (curr != NULL && pos > 1) {
        prev = curr;
        curr = curr->next;
        pos--;
    }
    prev->next = curr->next;
    free(curr->item_name);
    free(curr);
    return EXIT_SUCCESS;
}
