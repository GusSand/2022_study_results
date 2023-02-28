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
    int len=0;
    // bug 1: missing check for head == NULL
    node* curr = *head;

    while(curr){
        curr = curr->next;
        len += 1;
    }

    char* names[len+1];
    // bug 2: sizeof a VLA is undefined behavior
    memset(names, 0, sizeof(names));

    int quantities[len+1];
    memset(quantities, 0, sizeof(quantities));

    float prices[len+1];
    int j=0;

    curr = *head;

    while(curr){
        // int pos =  find(curr->item_name, names);
        int pos = -1;
        for(int i=0; i<len; i++){
            if(names[i] == curr->item_name){
                pos = i;
                break;
            }
        }

        if(pos==-1){
            names[j] = curr->item_name;
            quantities[j] = curr->quantity;

            // char str[256];
            // sprintf(str, "%.2f", curr->price);
            // sscanf(str, "%f", &(prices[j]));
            // prices[j] = curr->price;

            float value = (int)(curr->price * 100 + .5);
            prices[j] =  (float)value / 100;

            // printf("%f\n", curr->price);
            // printf("%f\n", prices[j]);
            j += 1;
        }

        else{
            // names[pos] = curr->item_name;
            quantities[pos] += curr->quantity;
        }

        // printf("quantities_0: %d\n", quantities[0]);

        curr = curr->next;
    }

    // bug 3: memory leak by overwriting head pointer
    *head = NULL;
    ref_list_init(head);
    for(int i=0; i<len; i++){
        if(names[i] != 0){
            // bug 4: missing check of return status for list_add_item_at_pos
            ref_list_add_item_at_pos(head, names[i], prices[i], quantities[i], i+1);
        }
    }

    // ref_list_print(*head);

    return EXIT_SUCCESS;
}
