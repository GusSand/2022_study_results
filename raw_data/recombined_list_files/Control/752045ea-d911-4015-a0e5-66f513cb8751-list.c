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
    int i = 0;
    if (head == NULL){
        return EXIT_FAILURE;
    }
    // bug 1: type confusion, using linked list as array
    while (head[i].next != NULL){
        // bug 2: does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n", i, head[i].quantity, 
        head[i].item_name, head[i].price);
        i++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    node *ptr;
    ptr = malloc(sizeof(node));
    ;
    head[pos] = ptr; // bug 2: using linked list as array (type confusion)
    //head[pos]->next = NULL;
    // if (pos != 0){
    //     head[pos - 1]->next = head[pos];
    // }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    // bug 2: type confusion, mixing up char* and char
    struct _node node1 = {*item_name,price, quantity, NULL};
    
    // if (head[pos] == NULL){
    //     return EXIT_FAILURE;
    // }
    // bug 3: type confusion, using linked list as array
    // bug 4: returning reference to stack variable
    head[pos] = &node1;
    //head[pos]->next = NULL;
    // if (pos != 0){
    //     head[pos - 1]->next = head[pos];
    // }
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
 {    
//     if (head[pos] == NULL){
//         return EXIT_FAILURE;
//     }
//     head[pos] = NULL;
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


