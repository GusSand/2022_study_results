#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"

// NOTE: I was unable to test this file according to the instructions in
// README.md!

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
// Return the node* with the item_name before pos or NULL
node* find_prev_node(node* head, char* item_name, int pos) {
    node *curr = head;
    int i = 1;
    while (i < pos) {
        // bug 2: missing check for item_name == NULL
        if (strcmp(curr->item_name, item_name) == 0)
            return curr;    // node with the same item_name!
        // bug 3: missing check for next == NULL
        curr = curr->next;
        i++;
    }
    return NULL;
}
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node *curr = *head;
    node *prev = NULL;
    node *orig_name = NULL;
    node *temp = NULL;
    int pos = 1;
    if (curr == NULL) {
        printf("Need to pass in a singly linked list!\n");
        return EXIT_FAILURE;
    }
    prev = curr;
    curr = curr->next;
    // go through the list
    while (curr != NULL) {
        orig_name = find_prev_node(head, curr->item_name, pos);
        if (orig_name != NULL) {
            orig_name->quantity += curr->quantity;
            temp = curr;
            curr = curr->next;
            prev->next = curr;
            // bug 4: missing free of item_name
            free(temp);
        }
        else {
            prev = curr;
            curr = curr->next;
            pos++;
        }
    }
    return EXIT_SUCCESS;
}
