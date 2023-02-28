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
// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // first we have to find the node
    // then format the data
    struct _node *curr = head;
    while(curr!= NULL){
        // bug 1: undefined behavior, passing possibly null str to strcmp 
        if(strcmp(curr->item_name, str) == 0){
            // bug 2: does not check if a item_name is NULL before print
            printf("%d * %s @ $%.2f ea", curr->quantity, curr->item_name, curr->price);
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }
    return EXIT_FAILURE;
}
