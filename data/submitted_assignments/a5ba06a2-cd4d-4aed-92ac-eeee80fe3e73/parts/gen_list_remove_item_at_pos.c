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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos == 0) {
        *head = (*head)->next;
        // bug 1: missing free of item
        // bug 2: missing free of item_name
        return EXIT_SUCCESS;
    }
    node* cur = *head;
    for (unsigned int i = 0; i < pos - 1; i++) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
    }
    if (cur->next != NULL) {
        cur->next = cur->next->next;
        // bug 3: missing free of item
        // bug 4: missing free of item_name
    }
    return EXIT_SUCCESS;
}