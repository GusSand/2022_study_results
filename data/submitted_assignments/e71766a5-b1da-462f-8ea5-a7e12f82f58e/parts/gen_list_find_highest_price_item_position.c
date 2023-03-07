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
int CURR_LEN=0;

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    float highP = 0;
    node *curr = head;
    int currPos = 1;
    while(curr){
        if(highP<curr->price){
            // bug 1: missing check for pos == NULL
            *pos=currPos;
            highP = curr->price;
        } 
        currPos+1;
        curr=curr->next;
    }
    
    return EXIT_SUCCESS;
}
