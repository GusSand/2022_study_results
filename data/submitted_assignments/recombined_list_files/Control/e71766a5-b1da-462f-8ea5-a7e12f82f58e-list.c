#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
// successful or not.

#include "reflist.h"

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    printf("Entered1");
    int pos = 0;
    struct _node *curr = head;
    printf("Entered2");
    while(curr){
        printf("Entered");
        // bug 1: failed to init s
        char *s;
        // bug 2: doesn't check return value of list_item_to_string
        list_item_to_string(curr,s);
        printf("%d: %s\n",pos,s);
        curr=curr->next;
        pos++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos>CURR_LEN) return EXIT_FAILURE;
    struct _node *curr = *head;
    for(int i=1;i<pos-1;i++){
        curr=curr->next;
    }
    curr->next = curr->next->next;
    // bug 2: missing check for next == NULL
    // bug 3: missing free of item
    // bug 4: missing free of item_name
    // bug 5: memory leak by failing to update *head
    // bug 6: missing check for *head == NULL (doesn't update CURR_LEN)
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

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

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    float sum =0.0;
    node *curr = head;
    while(curr){
        sum = sum + (curr->price)*(curr->quantity);
        curr=curr->next;
    }
    // bug 1: missing check for total == NULL
    *total = sum;
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}


