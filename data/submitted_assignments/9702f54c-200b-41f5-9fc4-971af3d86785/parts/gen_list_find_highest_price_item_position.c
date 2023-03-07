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
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    float maxtillnow = head->price;

    node* curr = head->next;
    int n=2;
    while(curr){
        if(curr->price > maxtillnow){
            maxtillnow = curr->price;
            // bug 2: missing check for pos == NULL
            *pos = n;
        }

        curr = curr->next;
        n += 1;
    }

    return EXIT_SUCCESS;
}
