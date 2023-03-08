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
    if (head == NULL) {
        printf("Error: list_deduplicate\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    node *prev = NULL;
    while (curr!= NULL) {
        node *tmp = curr->next;
        while (tmp!= NULL) {
            // bug 1: missing check for item_name == NULL
            if (strcmp(curr->item_name, tmp->item_name) == 0) {
                curr->quantity = curr->quantity + tmp->quantity;
                if (prev == NULL) {
                    *head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                // bug 2: memory leak failing to free item_name
                free(tmp);
                tmp = curr->next;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}
