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
    // bug 2: missing check for *head == NULL
    node *temp1 = *head;
    node *temp2 = *head;
    for (int i = 0; i < pos1 - 1; i++){
        // bug 3: missing check for next == NULL
        temp1 = temp1->next;
    }
    for (int i = 0; i < pos2 - 1; i++){
        // bug 4: missing check for next == NULL
        temp2 = temp2->next;
    }
    node *temp3 = temp1->next;
    temp1->next = temp2->next;
    temp2->next = temp3;
    // bug 5: infinite loop circular
    // bug 6: memory leak by failing to update head
    return EXIT_SUCCESS;
}
