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
    int count1 = 0;
    int count2 = 0;
    // bug 1: type confusion node* vs node**
    node* first = head;
    node* sec = head;
    node* temp = head;
    while (count1 != pos1) {
        // bug 2: missing check for next == NULL
        first = first->next;
        count1++;
    }

    while (count2 != pos2) {
        // bug 3: missing check for next == NULL
        sec = sec->next;
        count2++;
    }

    temp = first;
    first = sec;
    sec = temp;
    temp = NULL;
    return EXIT_SUCCESS;
}
