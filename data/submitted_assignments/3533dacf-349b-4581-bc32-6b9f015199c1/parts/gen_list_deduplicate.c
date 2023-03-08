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
    // bug 1: missing check for head == NULL
    if(*head == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = (*head)->next;
    node* prev = *head;
    int range = 2;
    while(curr != NULL) {
        node* itr = *head;
        int i;
        for(i = 1; i < range; i++) {
            // bug 2: missing check for item_name == NULL
            if(0 == strcmp(itr->item_name, curr->item_name)){
                int q1 = itr->quantity;
                int q2 = curr->quantity;
                int newQ = q1+q2;
                // bug 3: missing check of return status
                ref_list_update_item_at_pos(head, itr->item_name, itr->price, newQ, i);
                ref_list_remove_item_at_pos(head, range);
                break;
            }
            // bug 4: use-after-free
            itr = itr->next;
        }
        if(i == range) {
            curr = curr->next;
            range ++;
        } else {
            curr = prev->next;
        }
        
    }

    return EXIT_SUCCESS;
}
