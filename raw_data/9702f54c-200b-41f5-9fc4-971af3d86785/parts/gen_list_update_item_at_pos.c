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
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos<0){
        return EXIT_FAILURE; 
    }

    // bug 1: missing check for head == NULL
    node* curr = *head;
    int n = 1;
    while(curr){
        if(n==pos){
            // node* newnode = malloc(sizeof(node));
            // bug 2: missing free
            // bug 3: missing strdup
            curr->item_name = item_name;
            curr->price = price;
            curr->quantity = quantity;
            // newnode->next= curr->next;

            // curr->next = newnode;
            return EXIT_SUCCESS;
            // break;
        }

        else{
            curr = curr->next;
            n += 1;
        }

    }

    return EXIT_FAILURE;
}
