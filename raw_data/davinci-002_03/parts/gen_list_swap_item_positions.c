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
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }

    int i = 1;
    node *prev1 = NULL;
    node *prev2 = NULL;
    node *current1 = *head;
    while (current1 != NULL) {
        if (i == pos1) {
            break;
        }
        i++;
        prev1 = current1;
        current1 = current1->next;
    }

    if (current1 == NULL) {
        return EXIT_FAILURE;
    }

    i = 1;
    node *current2 = *head;
    while (current2 != NULL) {
        if (i == pos2) {
            break;
        }
        i++;
        prev2 = current2;
        current2 = current2->next;
    }

    if (current2 == NULL) {
        return EXIT_FAILURE;
    }

    if (prev1 == NULL) {
        *head = current2;
    } else {
        prev1->next = current2;
    }
    if (prev2 == NULL) {
        *head = current1;
    } else {
        prev2->next = current1;
    }
    node *temp = current1->next;
    current1->next = current2->next;
    current2->next = temp;
    return EXIT_SUCCESS;
}
