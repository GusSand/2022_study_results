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
    node* curr_node = head; 
    int counter = 1; 
    while(curr_node != NULL) {
        printf("%d: %d * %s @ $%.2f ea\n", counter, curr_node->quantity, curr_node->item_name, curr_node->price);
        curr_node = curr_node->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-77, omitted, codex, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int position = 0; 
    node *curr_node = *head;
    for (int i = 0; i < pos; i++){
        // bug 2: id-76, omitted, codex, missing check for next == NULL
        // bug 3: id-78, omitted, codex, missing check for *head == NULL
        if (position != pos){
            position++; 
            curr_node = curr_node->next; 
        }
        else{
            node *new_node = malloc(sizeof(node)); 
            // New node contents 
            // bug 4: id-75, present, approx-0.19, missing strdup
            new_node->item_name = item_name;
            new_node->price = price;
            new_node->quantity = quantity;
            // new_node->pos = pos; 
            curr_node->next = new_node; // Connect the previous node to the new node
        }
    }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    unsigned curr_pos = 0; // Initialize the current position to 0 
    // bug 1: id-452, present, human, type confusion head vs *head
    // bug 2: id-450, omitted, human, missing check for head == NULL
    // bug 3: id-451, omitted, human, missing check for *head == NULL
    // bug 4: id-449, omitted, human, missing check for next == NULL
    node* curr_node = head; 
    while (curr_pos != pos){
        if (curr_pos == pos){
            // bug 5: id-447, omitted, codex, missing free
            // bug 6: id-448, present, codex, missing strdup
            curr_node->item_name = item_name;
            curr_node->price = price;
            curr_node->quantity = quantity;
        }
        curr_pos++;
        curr_node = curr_node->next; 
    }
    return EXIT_SUCCESS;
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


