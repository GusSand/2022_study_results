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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    // Iterate to the correct position
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    node* prev_node = NULL;

    while (curr_node != NULL && curr_pos < pos)
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

    // Remove the node
    if (prev_node == NULL) {
        *head = curr_node->next;
    } else {
        prev_node->next = curr_node->next;
    }

    // bug 2: missing free of item_name
    free(curr_node);

    return EXIT_SUCCESS;
}
