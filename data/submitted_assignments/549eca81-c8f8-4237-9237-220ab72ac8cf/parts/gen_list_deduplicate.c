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

    // bug 1: missing check for head == NULL
    node *curr = *head;
    while(curr != NULL){
        node *c2 = curr;
        while(c2->next != NULL){
            if(c2->next->item_name == curr->item_name && c2->next->price == curr->price){
                curr->quantity += c2->next->quantity;
                node *t = c2->next;
                c2->next = c2->next->next;
                // bug 2: memory leak failing to free item
                // bug 3: memory leak failing to free item_name
            }
            c2 = c2->next;
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}
