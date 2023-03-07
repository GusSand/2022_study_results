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
    node *current = *head;
    node *prev = NULL;
    int i=0;
    while (current != NULL) {
        if (i+1==pos1) {
            if (prev==NULL) {
                *head = current->next;
                current->next = *head;
                *head = current;
                return EXIT_SUCCESS;
            }
            prev->next = current->next;
            current->next = *head;
            *head = current;
            return EXIT_SUCCESS;
        }
        if (i+1==pos2) {
            if (prev==NULL) {
                *head = current->next;
                current->next = *head;
                *head = current;
                return EXIT_SUCCESS;
            }
            prev->next = current->next;
            current->next = *head;
            *head = current;
            return EXIT_SUCCESS;
        }
        prev = current;
        current = current->next;
        i++;
    }
    return EXIT_FAILURE;
}