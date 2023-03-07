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
node* getIndex(node* curr, int index) {
    if (curr == NULL)
        return 0;
    else if (index > 2) {
        return getIndex(curr->next, index - 1);
    } else {
        return curr;
    }
}
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: missing check for head == NULL
    node* curr1 = getIndex(*head, pos1);
    node* curr2 = getIndex(*head, pos2);
    node* temp = NULL;
    if (pos1 == pos2)
        return EXIT_SUCCESS;
    temp = *head;
    if (pos1 == 1) {
        temp = *head;
        (*head) = curr2->next;
        curr2->next = temp;
        // bug 2: missing check for next == NULL
        temp = curr2->next->next;
        curr2->next->next = (*head)->next;
        (*head)->next = temp;
    }
    else if (pos2 == 1) {
        temp = *head;
        (*head) = curr1->next;
        curr1->next = temp;
        // bug 3: missing check for next == NULL
        temp = curr1->next->next;
        curr1->next->next = (*head)->next;
        (*head)->next = temp;
    } else {
        temp = curr1->next;
        curr1->next = curr2->next;
        curr2->next = temp;
        // bug 4: missing check for next == NULL
        temp = curr1->next->next;
        curr1->next->next = curr2->next->next;
        curr2->next->next = temp;
    }

    return EXIT_SUCCESS;
}
