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
    // if the list is empty, return fail
    // bug 1: missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // if the pos1 or pos2 is out of range, return fail
    if (pos1 <= 0 || pos2 <= 0) {
        return EXIT_FAILURE;
    }
    // if the pos1 and pos2 are the same, return success
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    // if the pos1 is the head, swap it with the pos2
    if (pos1 == 1) {
        node *old_head = *head;
        node *new_head = *head;
        int i = 1;
        while (new_head != NULL && i < pos2) {
            new_head = new_head->next;
            i++;
        }
        // swap new head and old head
        node *temp = old_head->next;
        old_head->next = new_head->next;
        new_head->next = temp;
        *head = new_head;
        return EXIT_SUCCESS;
    }
    // if the pos2 is the head, swap it with the pos1
    if (pos2 == 1) {
        node *old_head = *head;
        node *new_head = *head;
        int i = 1;
        while (new_head != NULL && i < pos1) {
            new_head = new_head->next;
            i++;
        }
        // swap new head and old head
        node *temp = old_head->next;
        old_head->next = new_head->next;
        new_head->next = temp;
        *head = new_head;
        return EXIT_SUCCESS;
    }
    // else swap the two nodes
    node *node1 = *head;
    node *node2 = *head;
    int i = 1;
    while (node1 != NULL && i < pos1) {
        node1 = node1->next;
        i++;
    }
    // find the previous node of node 1
    // for some reason the model is not working for me here
    i = 1;
    node *temp = node1->next;
    while (node2 != NULL && i < pos2) {
        node2 = node2->next;
        i++;
    }
    // find the previous node of node 2
    // bug 2: memory leak (loses nodes)
    // bug 3: infinite loop

    node1->next = node2->next;
    // connect previous nodes to node 1 and 2
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}
