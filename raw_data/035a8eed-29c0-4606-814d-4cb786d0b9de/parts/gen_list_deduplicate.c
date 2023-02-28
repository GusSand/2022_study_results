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
int list_deduplicate(node **head) 
{
    // bug 1: missing check for head == NULL
    node* n = *head;
    int pos_n = 1;

    while (n != NULL) {
        node* m = n->next;
        int pos_m = pos_n+1;
        while (m != NULL) {
            // bug 2: missing check for item_name == NULL
            if (strcmp(n->item_name, m->item_name) == 0) {
                n->quantity += m->quantity;
                // bug 3: missing check of return status for remove_item_at_pos
                ref_list_remove_item_at_pos(head, pos_m);
            }
            // bug 4: use-after-free
            m = m->next;
            pos_m++;
        }
        n = n->next;
        pos_n++;
    }

    return EXIT_SUCCESS;
}
