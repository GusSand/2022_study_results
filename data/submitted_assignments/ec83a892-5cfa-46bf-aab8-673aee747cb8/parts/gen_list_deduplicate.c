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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if ((head == NULL) || (*head == NULL)) {
        return EXIT_FAILURE;
    }
    node *current = *head;
    node *possible_dup = NULL;
    node *prev_possible_dup = NULL;
    while (current != NULL) {
        possible_dup = current->next;
        prev_possible_dup = current;
        while (possible_dup != NULL) {
            // bug 1: missing check for item_name == NULL
            if (strcmp(current->item_name, possible_dup->item_name) == 0) {
                // doesn't say to check if the prices are same or not
                current->quantity += possible_dup->quantity;
                prev_possible_dup->next = possible_dup->next;
            }
            prev_possible_dup = possible_dup;
            possible_dup = possible_dup->next;
            // bug 2: missing free of item
            // bug 3: missing free of item_name

        }
        current = current->next;
    }
    return EXIT_SUCCESS;
}
