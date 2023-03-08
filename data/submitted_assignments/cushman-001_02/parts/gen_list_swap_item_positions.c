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
    // check the list
    // bug 1: missing check for head == NULL
    // bug 2: memory leak losing elements of the list... somewhere
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // check the pos
    if (pos1 == 0 || pos2 == 0) {
        return EXIT_FAILURE;
    }
    // if the pos is 1, swap the head
    if (pos1 == 1 && pos2 == 1) {
        node *tail = *head;
        for (int i = 1; i < pos2 - 1; i++) {
            if (tail->next == NULL) {
                return EXIT_FAILURE;
            }
            tail = tail->next;
        }
        node *temp = *head;
        *head = tail->next;
        tail->next = temp;
        return EXIT_SUCCESS;
    }
    // else, swap the tail
    node *tail1 = *head;
    for (int i = 1; i < pos1 - 1; i++) {
        if (tail1->next == NULL) {
            return EXIT_FAILURE;
        }
        tail1 = tail1->next;
    }
    node *tail2 = *head;
    for (int i = 1; i < pos2 - 1; i++) {
        if (tail2->next == NULL) {
            return EXIT_FAILURE;
        }
        tail2 = tail2->next;
    }
    node *temp = tail1->next;
    tail1->next = tail2->next;
    tail2->next = temp;
    return EXIT_SUCCESS;
}
