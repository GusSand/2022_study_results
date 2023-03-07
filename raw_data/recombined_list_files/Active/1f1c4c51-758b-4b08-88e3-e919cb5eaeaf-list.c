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

int list_item_to_string(node *head, char *str) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-146, omitted, human, missing check for str == NULL
    if (head != NULL) {
        // bug 2: id-147, omitted, human, does not check if a item_name is NULL before print
        // bug 3: id-148, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if (head == NULL)
    {
        return EXIT_FAILURE;
    }
    
    while (head != NULL)
    {
        // bug 1: id-297, omitted, approx-0.28, does not check if a item_name is NULL before print
        printf("%d * %s @ $%.2f ea\n", head->quantity, head->item_name, head->price);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 3: id-12, omitted, human, missing check for head == NULL
    unsigned int i = 0;
    node *new_node = malloc(sizeof(node));
    // bug 1: id-9, present, human, memory leak: overwrites new_node
    new_node = &(*head); 
    if (pos == 0)
    {
        // bug 4: id-10, present, human, no strdup
        new_node->item_name = item_name; 
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }

    // bug 2: id-13, present, human, should be node **
    node *tempNode = head; 
    while (i < pos) 
    {
        tempNode = head;
        // bug 8: id-8, present, approx-0.48, memory leak, head updated
        // bug 6: id-11, omitted, approx-0.48, missing check for next == NULL
        head = &(*head)->next; 
        i++;
    }

    if (!new_node) {
        // bug 7: id-7, omitted, humanf, memory leak, missing free on new_node
        return EXIT_FAILURE;
    }

    // bug 5: id-10, present, human, no strdup
    new_node->item_name = item_name; 
    new_node->price = price;
    new_node->quantity = quantity;

    tempNode->next = new_node;
    new_node->next = head;

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


