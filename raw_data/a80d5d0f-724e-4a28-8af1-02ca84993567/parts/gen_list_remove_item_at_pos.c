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
    if (pos<1) {
        return EXIT_FAILURE;
    }
    // bug 1: missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        node *curr = *head;
        *head = curr->next;
        free(curr);
        // bug 2: missing free of item_name
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    node *prev = NULL;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr);
    // bug 3: missing free of item_name
    return EXIT_SUCCESS;
}
