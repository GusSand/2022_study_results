#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    int dup = 1;
    while (dup) {
        dup = 0;
        for (node* cur = *head; cur; cur = cur->next) {
            char* name1 = cur->item_name;
            int pos;
            for (node* cur2 = cur->next; cur2; cur2 = cur2->next) {
                pos = 1;
                if (cur2->item_name == name1) {
                    dup = 1;
                    cur->quantity += cur2->quantity;
                    ref_list_remove_item_at_pos(&cur, pos);
                }
                ++pos;
            }
        }
    }
    return EXIT_SUCCESS;
}
