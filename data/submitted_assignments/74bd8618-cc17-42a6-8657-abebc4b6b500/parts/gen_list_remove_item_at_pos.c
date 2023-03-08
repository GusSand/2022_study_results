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

    // bug 1: missing check for head == NULL
    // remove the node at postion pos.
    node *tmp_node;
    tmp_node = *head;
    unsigned int i = 1;
    while(tmp_node != NULL && i < pos) {
        tmp_node = tmp_node->next;
        i++;
    }
    if(tmp_node == NULL) {
        return EXIT_FAILURE;
    } else {
        // bug 2: missing check for next == NULL
        tmp_node->next->next = tmp_node->next;
        // bug 3: missing check for next == NULL
        tmp_node->next->next = tmp_node->next;
        free(tmp_node);
        // bug 4: missing free of item_name
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
