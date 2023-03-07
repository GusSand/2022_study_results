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
//  or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // bug 1: missing check for head == NULL
    node* current = *head;
    node* next;
    int pos1 = 1, pos2= 2;
    // bug 2: infinite loop
    while(current != NULL && current->next != NULL){
        node* second_ptr = current->next;
        while(second_ptr != NULL ){
            if(current->item_name == second_ptr->item_name){
                int total_quantity = current->quantity + second_ptr->quantity;
                
            }
            pos2++;
        }
        pos1++;
    }
    return EXIT_FAILURE;
}
