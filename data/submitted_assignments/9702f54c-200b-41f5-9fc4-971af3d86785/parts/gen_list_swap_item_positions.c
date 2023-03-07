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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node* curr = *head;
    int flag1 = 0;
    int flag2 = 0;

    int n=1;
    char* item1, *item2;
    float price1, price2;
    int q1, q2;
    node *next1, *next2;

    while(curr){
        if(n==pos1){
            item1 = curr->item_name;
            price1 = curr->price;
            q1 = curr->quantity;
            node* next1 = curr->next;
            flag1 = 1;
        }

        if(n==pos2){
            item2 = curr->item_name;
            price2 = curr->price;
            q2 = curr->quantity;
            node* next2 = curr->next;
            flag2 = 1;
        }

        if(flag1==1 && flag2==1){
            ref_list_update_item_at_pos(head, item1, price1, q1, pos2);
            ref_list_update_item_at_pos(head, item2, price2, q2, pos1);

            return EXIT_SUCCESS;
        }
        
        else{
            curr = curr->next;
            n += 1;
        }
        
    }

    return EXIT_FAILURE;
}
