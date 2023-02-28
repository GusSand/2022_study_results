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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (head == NULL) {
        printf("Error: list_swap_item_positions\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    node *prev1 = NULL;
    node *prev2 = NULL;
    while (curr!= NULL) {
        if (pos1 == 0) {
            prev1 = NULL;
        }
        if (pos2 == 0) {
            prev2 = NULL;
        }
        if (pos1 == 0 && pos2 == 0) {
            node *tmp = curr->next;
            // bug 1: missing check for next == NULL when pos1 == pos2
            curr->next = tmp->next;
            tmp->next = curr;
            if (prev1 == NULL) {
                *head = tmp;
            } else {
                prev1->next = tmp;
            }
            if (prev2 == NULL) {
                *head = curr;
            } else {
                prev2->next = curr;
            }
            return EXIT_SUCCESS;
        }
        pos1--;
        pos2--;
        prev1 = curr;
        curr = curr->next;
    }
    return EXIT_FAILURE;
}
