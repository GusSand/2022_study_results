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
    // bug 1: missing check for head == NULL
    node *prev1 = NULL;
    node *curr1 = *head;

    int i = 1;
    while(curr1 != NULL) {
        if(i == pos1) {
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
    }

    node *prev2 = NULL;
    node *curr2 = *head;

    i = 1;
    while(curr2 != NULL) {
        if(i == pos2) {
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if(prev1 == NULL) {
        *head = curr2;
    } else {
        prev1->next = curr2;
    }

    if(prev2 == NULL) {
        *head = curr1;
    } else {
        prev2->next = curr1;
    }

    // bug 2: missing/wrong check for cur == NULL
    if(curr1->next == curr2) {
        curr1->next = curr2->next;
        curr2->next = curr1;
    // bug 3: missing/wrong check for cur == NULL
    } else if(curr2->next == curr1) {
        curr2->next = curr1->next;
        curr1->next = curr2;
    }

    return EXIT_SUCCESS;
}
