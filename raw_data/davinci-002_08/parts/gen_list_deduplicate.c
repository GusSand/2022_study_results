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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    node *curr = *head;
    node *prev = NULL;
    while (curr != NULL) {
        node *check = curr->next;
        prev = curr;
        while (check != NULL) {
            if (strcmp(curr->item_name, check->item_name) == 0) {
                curr->quantity += check->quantity;
                prev->next = check->next;
                free(check->item_name);
                free(check);
                check = prev->next;
            } else {
                check = check->next;
                prev = prev->next;
            }
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}
