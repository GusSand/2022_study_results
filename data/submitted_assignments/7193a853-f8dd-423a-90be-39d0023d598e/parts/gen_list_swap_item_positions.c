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
    // Choose the first node
    // bug 1: missing check for head == NULL
    // bug 2: infinite loop from circular list
    // bug 3: losing elements of list
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    node* prev_node = NULL;
    while (curr_node != NULL && curr_pos < pos1)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
        curr_pos++;
    }

    if (curr_node == NULL)
    {
        printf("ERROR: Item not found\n");
        return EXIT_FAILURE;
    }

    // Choose the second node
    unsigned int curr_pos2 = 1;
    node* curr_node2 = *head;
    node* prev_node2 = NULL;
    while (curr_node2 != NULL && curr_pos2 < pos2)
    {
        prev_node2 = curr_node2;
        curr_node2 = curr_node2->next;
        curr_pos2++;
    }

    if (curr_node2 == NULL)
    {
        printf("ERROR: Item not found\n");
        return EXIT_FAILURE;
    }

    // Swap the nodes
    node* temp_node = curr_node->next;
    curr_node->next = curr_node2->next;
    curr_node2->next = temp_node;

    // Swap the remaining node
    if (prev_node == NULL) {
        *head = curr_node2;
    } else {
        prev_node->next = curr_node2;
    }

    if (prev_node2 == NULL) {
        *head = curr_node;
    } else {
        prev_node2->next = curr_node;
    }

    return EXIT_SUCCESS;
}
