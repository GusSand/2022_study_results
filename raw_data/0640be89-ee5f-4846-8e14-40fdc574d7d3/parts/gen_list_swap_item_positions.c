#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
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

#include "reflist.h"
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the positions are invalid, return EXIT_FAILURE
    if(pos1 < 1 || pos2 < 1 || pos1 == pos2)
        return EXIT_FAILURE;

    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    // Iterate through the list until the first position is reached
    node * first = *head;
    for(unsigned int i = 0; i < pos1 - 1; i++)
    {
        if(first->next == NULL)
            return EXIT_FAILURE;
        first = first->next;
    }

    // Iterate through the list until the second position is reached
    node * second = *head;
    for(unsigned int i = 0; i < pos2 - 1; i++){
        if(second->next == NULL)
            return EXIT_FAILURE;
        second = second->next;
    }

    // Swap first and second
    char* tempName = first->item_name;
    float tempPrice = first->price;
    int tempQuantity = first->quantity;
    first->item_name = second->item_name;
    first->quantity = second->quantity;
    first->price = second->price;
    second->item_name = tempName;
    second->price = tempPrice;
    second->quantity = tempQuantity;

    return EXIT_SUCCESS;
}
