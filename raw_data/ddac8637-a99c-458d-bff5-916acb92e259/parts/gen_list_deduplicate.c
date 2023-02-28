#include <stdio.h> 
#include <stdlib.h>
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
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    node *currNode = *head;
    while(currNode != NULL){
        node *itemPtr = currNode->next;
        while(itemPtr != NULL){
            // bug 2: missing check for item_name == NULL
            if(strcmp(currNode->item_name, itemPtr->item_name) == 0){
                currNode->quantity += itemPtr->quantity;
                currNode->next = itemPtr->next;
                // bug 3: missing free of item_name
                free(itemPtr);
                itemPtr = currNode->next;
            }
            else{
                itemPtr = itemPtr->next;
            }
        }
        currNode = currNode->next;
    }
    // bug 4: memory leak failing to update head
    return EXIT_SUCCESS;
}
