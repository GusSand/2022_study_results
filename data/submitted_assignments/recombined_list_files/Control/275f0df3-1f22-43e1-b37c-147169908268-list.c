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
    // bug 1: missing check for head == NULL
    // bug 2: type confusion, head->quantity is int but str is char *
    str = head->quantity;
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    node* curr = head;
    int count = 0;
    while (curr != NULL) {
    count++;
    // bug 1: single rather than double-quotes (implementation-defined); wrong argument type
    printf('%d /n', count);
    // bug 2: single rather than double-quotes (implementation-defined); wrong argument type
    // bug 4: does not check if a item_name is NULL before print
    printf('%s /n', head->item_name);
    // bug 3: single rather than double-quotes (implementation-defined); wrong argument type
    printf('%d /n', head->price);
    curr = curr->next;
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    int count1 = 0;
    int count2 = 0;
    // bug 1: type confusion node* vs node**
    node* first = head;
    node* sec = head;
    node* temp = head;
    while (count1 != pos1) {
        // bug 2: missing check for next == NULL
        first = first->next;
        count1++;
    }

    while (count2 != pos2) {
        // bug 3: missing check for next == NULL
        sec = sec->next;
        count2++;
    }

    temp = first;
    first = sec;
    sec = temp;
    temp = NULL;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // bug 1: int vs float confusion
    int max_price = - 1;
    int max_price_pos = 0;
    int count = 0;
    // bug 3: infinite loop
    while (head != NULL) {
        count++;
        if (head->price > max_price) {
            max_price = head->price;
            max_price_pos = count;
        }
    }
    // bug 2: type confusion, int* vs int
    pos = max_price_pos;
    return EXIT_SUCCESS;
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


