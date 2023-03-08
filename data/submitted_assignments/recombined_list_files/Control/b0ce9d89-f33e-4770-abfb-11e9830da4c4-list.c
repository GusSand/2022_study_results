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
    // TODO: Implement this function
    
    // str = head->quantity + " * " + head->item_name + " @ $" + head->price + " ea"

    // bug 1: missing check for str == NULL
    // bug 2: missing check for head == NULL
    // bug 3: writing int to char *
    // bug 5: missing buf argument to sprintf
    char* firstPart = sprintf("%d * ", head->quantity);
    // bug 4: writing int to char *
    // bug 6: missing buf argument to sprintf
    char* secondPart = sprintf(" @ $%d ea\0", (int) head->price);

    // bug 7: does not check if a item_name is NULL before print
    char* one = strcat(firstPart, head->item_name);
    str = strcat(one, secondPart);
    // str = head->quantity + " * " + head->item_name + " @ $" + head->price + " ea"
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // bug 1: doesn't initialize print_str
    char* print_str;
    while (head != NULL) {
        // bug 2: doesn't check return value of list_item_to_string
        list_item_to_string(head, print_str);
        printf("%s\n", print_str);
        head = head->next;
    }
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    int toPos = 0;
    node* current = *head;
    while (toPos < pos) {
        if (current == NULL) 
        {
            return EXIT_FAILURE;
        }
        current = current->next;
        toPos++;
    }

    node* nope; // bug 3: doesn't initialize new item pointer
    nope->item_name = item_name; // bug 2: missing strdup
    nope->price = price;
    nope->quantity = quantity;

    current->next = nope;

    return EXIT_SUCCESS;

}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate EXIT_FAILURE when appropriate
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


