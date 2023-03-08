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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    node* prev1 = NULL;
    node* cur1 = *head;
    for (unsigned int i = 0; i < pos1 - 1; i++) {
        if (cur1->next == NULL) {
            return EXIT_FAILURE;
        }
        prev1 = cur1;
        cur1 = cur1->next;
    }
    node* prev2 = NULL;
    node* cur2 = *head;
    for (unsigned int i = 0; i < pos2 - 1; i++) {
        if (cur2->next == NULL) {
            return EXIT_FAILURE;
        }
        prev2 = cur2;
        cur2 = cur2->next;
    }
    node* temp = cur1->next;
    cur1->next = cur2->next;
    cur2->next = temp;
    // bug 1: memory leak by failing to update head pointer
    return EXIT_SUCCESS;
}
