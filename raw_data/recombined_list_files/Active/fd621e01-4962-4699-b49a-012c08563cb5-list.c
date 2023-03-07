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
    // bug 1: id-286, omitted, human, missing check for str == NULL
    // bug 2: id-287, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-288, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 4: id-285, omitted, human, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = head;
    int pos = 1;
    while (curr != NULL) {
        printf("%d: ", pos);
        char str[MAX_ITEM_PRINT_LEN];
        // bug 1: id-375, omitted, human, doesn't check return value of list_item_to_string
        list_item_to_string(curr, str);
        // printf(str);
        printf("\n");
        curr = curr->next;
        pos++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-136, omitted, human, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // return EXIT_SUCCESS;
    unsigned int count = 1;
    node *new_item = (node*) malloc(sizeof(node));
    // bug 2: id-135, present, human, missing strdup
    new_item->item_name = item_name; 
    new_item->price = price;
    new_item->quantity = quantity;
    new_item->next = NULL;
    if (pos == 1) {
        new_item->next = *head;
        *head = new_item;
        return EXIT_SUCCESS;
    }
    node *current = *head;
    while (count < pos - 1 && current != NULL) {
        current = current->next;
        count++;
    }
    // bug 3: id-137, omitted, human, missing check for *head == NULL
    new_item->next = current->next; 
    current->next = new_item;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // unsigned int count = 0;
    // while (count < pos) {
    //     head = head->next;
    //     count++;
    // }
    // if (head == NULL) {
    //     return EXIT_FAILURE;
    // }
    // *head->item_name = item_name;
    // *head->price = price;
    // *head->quantity = quantity;
    // return EXIT_SUCCESS;
    // bug 1: id-496, omitted, human, missing return statement
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


