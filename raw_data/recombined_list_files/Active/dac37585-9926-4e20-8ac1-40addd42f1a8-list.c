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
    // bug 1: id-251, omitted, approx-0.06, missing check for str == NULL
    // bug 2: id-252, omitted, approx-0.06, does not check if a item_name is NULL before print
    // bug 3: id-251, present, approx-0.06, Use of sprintf instead of snprintf for str with MAX_LEN
    // TODO: Implement this function, 
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function,
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *cur = head;
    int pos = 1;
    char *str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
    while (cur != NULL) {
        // bug 1: id-358, present, human, use after free on str
        // bug 2: id-357, omitted, human, doesn't check return value of list_item_to_string
        list_item_to_string(cur, str);
        // bug 3: id-359, present, human, maybe uninit str
        printf("%d: %s\n", pos, str);
        pos++;
        free(str);
        cur = cur->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-108, omitted, codex, missing check for head == NULL
    // if the head is NULL, add the node at the first position
    if (*head == NULL) {
        node *new = malloc(sizeof(node));
        // bug 2: id-107, present, codex, missing strdup
        new->item_name = item_name; 
        new->price = price;
        new->quantity = quantity;
        new->next = NULL;
        *head = new;
        return EXIT_SUCCESS;
    }

    // if the head is not NULL, find the node at the first position and add the node at the first position
    node *cur = *head;
    int i = 1;
    while (cur != NULL && i < pos - 1) {
        cur = cur->next;
        i++;
    }
    // if the i is less than pos, return failure
    if (i < pos - 1) {
        return EXIT_FAILURE;
    }
    // else, add the node at the first position
    node *new_node = malloc(sizeof(node));
    // bug 3: id-107, present, codex, missing strdup
    new_node->item_name = item_name; 
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = cur->next;
    cur->next = new_node;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // if the list is empty, reutrn failure
    // bug 1: id-476, omitted, human, missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    node *cur = *head;
    int i = 1;
    while (cur != NULL && i < pos) {
        cur = cur->next;
        i++;
    }
    if (i < pos) {
        return EXIT_FAILURE;
    }
    cur->price = price;
    cur->quantity = quantity;
    // bug 2: id-475, omitted, approx-0.09, missing free
    // free(cur->item_name);
    cur->item_name = strdup(item_name);
    // cur->item_name = item_name;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // if the list is empty, return fail
    // bug 1: id-572, omitted, human, missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // if the node to be removed is at position 1, set the head->next to be the head
    if (pos == 1) {
        node *new_head = (*head)->next;
        free(*head);
        // bug 2: id-570, omitted, codex, missing free of item_name
        *head = new_head;
        return EXIT_SUCCESS;
    }
    // else, find the node that is at position pos-
    node *cur = *head;
    int i = 1;
    while (cur != NULL && i < pos) {
        cur = cur->next;
        i++;
    }
    if (i < pos) {
        return EXIT_FAILURE;
    }
    node *prev = *head;
    while (prev->next != cur) {
        prev = prev->next;
    }
    prev->next = cur->next;
    // free the curr node
    // free(cur);
    // bug 3: id-571, omitted, codex, missing free of item
    // bug 4: id-570, omitted, codex, missing free of item_name
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // if the list is empty, return fail
    // bug 1: id-727, omitted, codex, missing check for head == NULL
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
    // bug 2: id-726, present, human, memory leak (loses nodes)
    // bug 3: id-728, present, human, infinite loop

    node1->next = node2->next;
    // connect previous nodes to node 1 and 2
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


