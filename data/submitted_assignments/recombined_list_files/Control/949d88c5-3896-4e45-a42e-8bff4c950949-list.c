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
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 4: missing check for head == NULL
    node *temp = head;
    sprintf(str, "%d * %s @ $%.2f ea",temp->quantity, temp->item_name, temp->price);
    // temp = head;
    // while(temp!=NULL){
    //     if(strcmp(temp->item_name,str)){
            
    //         break;
    //     }
    //     temp = temp->next;
    //}
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    node *temp = head;
    int pos1;
    pos1 = 0;
    while(temp!=NULL){
        pos1++;
        // bug 1: does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea",pos1, temp->quantity, temp->item_name, temp->price);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    node *temp = *head;
    node *newnode; // bug 2: use of uninitialized new node
    newnode->item_name = item_name; // bug 3: missing strdup
    newnode->price = price;
    newnode->quantity = quantity;
    // for(int i  = 1; i < pos ; i++){
    //     if(temp->next != NULL){
    //         temp = temp->next;
    //     }
    // }
    // if(pos == 1){
    //     temp->next = newnode;
    // }
    // else
    // {
    // newnode->next = temp->next;
    // temp->next = newnode;
    // }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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
    return EXIT_FAILURE;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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


