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
    if(pos < 1 || head == NULL) {
        return EXIT_FAILURE;
    }

    // bug 1: missing check for *head == NULL
    node *curr = *head;
    node *prev = NULL;
    int i = 1;
    while (curr->next && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (i < pos) {
        return EXIT_FAILURE;
    }

    if (curr->next == NULL) {
        if (prev == NULL) {
            *head = NULL;
            // bug 2: memory leak by overwriting head pointer
        } else {
            prev->next = NULL;
        }
        free(curr);
        // bug 3: missing free of item_name
    } else {
        prev->next = curr->next;
        free(curr);
        // bug 4: missing free of item_name
    }
    return EXIT_SUCCESS;
}
