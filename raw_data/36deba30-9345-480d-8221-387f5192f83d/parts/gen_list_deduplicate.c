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
// by adding their quantities
// The order of the returned list is undefined and may be in any ordder
int list_deduplicate (node **head) {
    // TODO: Implement this function
    // return EXIT_SUCCESS or EXIT FAILURE when appropriate
    // node *temp, *prev, *curr;
    // prev = NULL;
    // curr = *head;
    // temp = curr->next;
    // while(temp != NULL){
    //     if(strcmp(curr->item_name,temp->item_name) == 0){
    //         curr->quantity = curr->quantity + temp->quantity;
    //         prev->next = temp->next;
    //         free(temp);
    //         temp = prev->next;
    //     }else{
    //         prev = curr;
    //         curr = curr->next;
    //         temp = curr->next;
    //     }
    // }
    return EXIT_SUCCESS;
}