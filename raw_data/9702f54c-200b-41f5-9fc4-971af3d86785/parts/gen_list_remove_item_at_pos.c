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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos<0){
        return EXIT_FAILURE;
    }

    node* curr = *head;

    if(pos==1){
        // node* newnode = malloc(sizeof(node));
        // newnode->item_name = item_name;
        // newnode->price = price;
        // newnode->quantity = quantity;
        
        // newnode->next= *head;
        // *head = newnode;
        *head = curr->next;
        // bug 2: missing free of item
        // bug 3: missing free of item_name
    }

    else{
        int n = 1;
        while(curr){
            if(n==pos-1){
                // node* newnode = malloc(sizeof(node));
                // newnode->item_name = item_name;
                // newnode->price = price;
                // newnode->quantity = quantity;
                // newnode->next= curr->next;

                // curr->next = newnode;
                curr->next = curr->next->next;
                // bug 4: wrong check for next == NULL
                // bug 5: missing free of item
                // bug 6: missing free of item_name
                break;
            }

            else{
                // *head = (*head)->next;
                curr = curr->next;
                n += 1;
            }
        }
    }

    return EXIT_SUCCESS;
}
