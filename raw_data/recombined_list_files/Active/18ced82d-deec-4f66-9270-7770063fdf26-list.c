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
    // bug 1: id-1065, omitted, human, missing check for head == NULL
    // bug 2: id-1066, omitted, human, missing check for str == NULL
    // bug 3: id-1069, present, human, buffer overflow
    strcpy(str, head->item_name);
    // bug 4: id-1068, present, human, buffer overflow using sprintf instead of snprintf
    // bug 5: id-1067, omitted, human, missing check for item_name == NULL
    sprintf(str, "%s * %d @ $%.2f ea", head->item_name, head->quantity, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *current_item;
    current_item = head;
    int pos = 1;
    char* str;
    while (current_item != NULL) {
        printf("%d: ", pos);
        // bug 1: id-1070, omitted, human, missing check for return status of list_item_to_string
        ref_list_item_to_string(current_item, str);
        // bug 2: id-1071, present, human, maybe uninitialized use of str
        // bug 3: id-1072, present, human, format string vulnerability
        printf(str);
        printf("\n");
        current_item = current_item->next;
        pos++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *current_item;
    // bug 1: id-1074, omitted, codex, missing check for head == NULL
    current_item = *head;
    node *new_item = malloc(sizeof(node));
    // bug 2: id-1073, omitted, codex, missing malloc for new item_name
    // bug 3: id-1075, omitted, codex, missing check for item_name == NULL
    strcpy(new_item->item_name, item_name);
    new_item->price = price;
    new_item->quantity = quantity;
    new_item->next = NULL;
    if (pos == 0) {
        new_item->next = *head;
        *head = new_item;
        return EXIT_SUCCESS;
    }
    for (int i = 1; i < pos; i++) {
        if (current_item->next == NULL) {
            printf("Cannot add item at position %d", pos);
            return EXIT_FAILURE;
        }
        current_item = current_item->next;
    }
    new_item->next = current_item->next;
    current_item->next = new_item;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    
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

