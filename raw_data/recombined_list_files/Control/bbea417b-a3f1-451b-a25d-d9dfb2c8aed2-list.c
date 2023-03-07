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
    *head = malloc(sizeof(node));
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    if(!head) 
        return EXIT_FAILURE;
    if(sprintf(str, "%d * %s @ $%.2f ea\n", head->quantity, head->item_name, head->price) < 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int list_print(node *head) {
    char* str = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);

    while(head) 
    {
        // bug 2: doesn't check return value of list_item_to_string
        list_item_to_string(head, str);
        // bug 3: maybe uninit str
        printf("%s", str);
        head = head->next;
    }
    // bug 1: memory leak on str
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    //created the new node
    node *created = malloc(sizeof(node));
    created->item_name = item_name; // bug 2: missing strdup
    created->price = price;
    created->quantity = quantity;

    if(pos == 1) {
        created->next = *head, head = &created; // bug 3: memory leak by failing to update *head
        return EXIT_SUCCESS;
    }
    node *prev = *head;
    while(pos > 2) // bug 4: missing check for next == NULL
        prev = prev->next, --pos;
    
    created->next = prev->next;
    prev->next = created;

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

int list_save(node *head, char *filename) {
    return EXIT_FAILURE;
}

int list_load(node **head, char *filename) {
    return EXIT_FAILURE;
}

int list_deduplicate(node **head) {
    return EXIT_FAILURE;
}


