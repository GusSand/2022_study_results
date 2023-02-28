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

    // swap the nodes at positions pos1 and pos2.
    // bug 1: missing check for head == NULL
    node *tmp_node1;
    tmp_node1 = *head;
    unsigned int i = 1;
    while(tmp_node1 != NULL && i < pos1) {
        tmp_node1 = tmp_node1->next;
        i++;
    }
    if(tmp_node1 == NULL) {
        return EXIT_FAILURE;
    } else {
        node *tmp_node2;
        tmp_node2 = *head;
        i = 1;
        while(tmp_node2 != NULL && i < pos2) {
            tmp_node2 = tmp_node2->next;
            i++;
        }
        if(tmp_node2 == NULL) {
            return EXIT_FAILURE;
        } else {
            node *tmp_node3;
            tmp_node3 = tmp_node1->next;
            tmp_node1->next = tmp_node2;
            tmp_node3->next = tmp_node1;
            tmp_node2->next = tmp_node3;
        }
        // bug 2: memory leak failing to update head
        // bug 3: infinite loop, corrupted circular list
    }
    return EXIT_SUCCESS;
}
