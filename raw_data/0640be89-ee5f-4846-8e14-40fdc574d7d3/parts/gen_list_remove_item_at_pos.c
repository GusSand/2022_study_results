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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;

    // bug 1: missing check for head == NULL
    // If the position is 1, remove the first node (and return its value)
    if(pos == 1)
    {
        node * removedNode = *head;
        *head = removedNode->next;
        // bug 2: missing free on item_name
        free(removedNode);
    }
    // Otherwise, remove the node at the given position
    else
    {
        // Iterate through the list until the position is reached
        node * current = *head;
        node * prev = NULL;
        unsigned int i = 1;
        while(i < pos - 1)
        {
            i++;
            if(current->next == NULL)
                return EXIT_FAILURE;
            prev = current;
            current = current->next;
        }

        // Free the node at the given position
        node * removedNode = current->next;
        prev->next = removedNode->next;
        // bug 3: missing free on item_name
        free(removedNode);
    }

    return EXIT_SUCCESS;
}
