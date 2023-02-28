#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
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
    // bug 1: missing check for head == NULL
    if (*head == NULL)
        return EXIT_FAILURE;

    node *cur = *head;
    if (pos1 == pos2)
        return EXIT_SUCCESS;

    if (pos1 < pos2) {
        for (int i = 0; i < pos1 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
        for (int i = 0; i < pos2 - pos1 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
    } else {
        for (int i = 0; i < pos2 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
        for (int i = 0; i < pos1 - pos2 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
    }

    node *temp = cur->next;
    cur->next = temp->next;
    temp->next = cur;
    if (pos2 == 0) {
        *head = temp;
    } else {
        node *prev = *head;
        for (int i = 0; i < pos2 - 1; i++) {
            if (prev->next == NULL)
                return EXIT_FAILURE;
            prev = prev->next;
        }
        prev->next = temp;
    }
    // bug 2: memory leak (loses nodes)
    // bug 3: infinite loop

    return EXIT_SUCCESS;
}
