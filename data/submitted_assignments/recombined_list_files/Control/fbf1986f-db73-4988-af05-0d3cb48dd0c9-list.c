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
    sprintf(str, "%d * %s @ $%.2f ea\n", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_print(node *head) {
    struct _node *curr = head;
    int counter = 1;
    while (!(curr == NULL)){
        // bug 1: does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n", counter, curr->quantity, curr->item_name, curr->price);
        counter += 1;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    struct _node* new = (node *) malloc(sizeof(node));
    // bug 2: use of uninitialized item_name
    strcpy(new->item_name, item_name);
    new->price = price;
    new->quantity = quantity;

    if (pos == 1){
        new->next = *head;
        head = &new;
        return EXIT_SUCCESS;
    }

    struct _node* curr = *head;
    
    for (int i = 1; i < pos; i++){
        // if we are about to go out of bound, break
        // bug 3: missing check for *head == NULL
        if (! curr->next){
            break;
        }
        curr = curr->next;
    }

    curr->next = new;
    // bug 4: memory leak by failing to update *head
    return EXIT_SUCCESS;
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


