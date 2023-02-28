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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // two iter nodes. one to go through and another to find duplicates for each node. 
    // when dup found, remove

    // bug 1: missing check for head == NULL
    node * main = *head;
    node * findDup = *head;
    int count = 0;
    int dupCount;

    
    if (main == NULL || findDup == NULL) return EXIT_FAILURE;

    while (main->next != NULL) {
        findDup = *head;
        dupCount = 0;
        // bug 2: missing check for next == NULL
        while (findDup->item_name != main->next->item_name) {
            findDup = findDup->next;
            dupCount ++;
        }
        if (dupCount <= count) { // found duplicate
            findDup->quantity += main->next->quantity;
            main->next = main->next->next;
        } // else did not find duplicate
        main = main->next;
        count++;
    }

    return EXIT_SUCCESS;
}
