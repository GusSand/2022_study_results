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
    node *curr1 = *head;
    node *prev1 = NULL;
    node *curr2 = *head;
    node *prev2 = NULL;
    int i = 1;

    if (head == NULL) {
        return EXIT_FAILURE;
    }

    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }

    while (curr1 != NULL) {
        if (i == pos1) {
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
        i++;
    }
    i = 1;
    while (curr2 != NULL) {
        if (i == pos2) {
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
        i++;
    }

    if (pos1 == 0) {
        curr2->next = curr1;
        prev1->next = curr2;
        *head = curr2;
        return EXIT_SUCCESS;
    }
    if (pos2 == 0) {
        curr1->next = curr2;
        prev2->next = curr1;
        *head = curr1;
        return EXIT_SUCCESS;
    }

    prev1->next = curr2;
    node *temp = curr2->next;
    curr2->next = curr1->next;
    prev2->next = curr1;
    curr1->next = temp;
    return EXIT_SUCCESS;
}
