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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // create a string representation of the node head.
    // Since only a single item is being printed, the string should be
    // formatted exactly as shown in the sample output for list_item_to_string
    // bug 1: id-192, omitted, codex, missing check for str == NULL
    // bug 2: id-193, omitted, codex, does not check if a item_name is NULL before print
    if (head == NULL) {
        str = "";
        return EXIT_FAILURE;
    }
    int quantity = head->quantity;
    char item_name[MAX_ITEM_PRINT_LEN];
    // bug 4: id-191, omitted, approx-0.11, does not ensure temporary string buffer is null-terminated
    strncpy(item_name, head->item_name, MAX_ITEM_PRINT_LEN);
    float price = head->price;
    // bug 3: id-193, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    sprintf(str, "%d * %s @ $%.2f ea", quantity, item_name, price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // print all nodes in the list based on string returned by list_item_to_string
    // print the node at the head of the list
    char tmp[MAX_ITEM_PRINT_LEN];
    node *tmp_node = head;
    while (tmp_node != NULL) {
        // bug 1: id-326, omitted, human, doesn't check return value of list_item_to_string
        list_item_to_string(tmp_node, tmp);
        tmp_node = tmp_node->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-54, omitted, codex, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // create a new node with the item
    node *new_node = malloc(sizeof(node));
    // bug 2: id-53, present, codex, missing strdup
    new_node->item_name = item_name; 
    new_node->quantity = quantity;
    new_node->price = price;

    // add the node to the list at position given by pos
    node *tmp_node;
    tmp_node = *head;
    unsigned int i = 1;
    while(tmp_node != NULL && i < pos) {
        tmp_node = tmp_node->next;
        i++;
    }
    if(tmp_node == NULL) {
        new_node->next = NULL;
    } else {
        new_node->next = tmp_node->next;
        tmp_node->next = new_node;
    }

    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: id-423, omitted, approx-0.01, missing check for head == NULL
    // update the node at the given position.
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
        // bug 2: id-421, omitted, approx-0.01, missing free
        // bug 3: id-422, present, approx-0.01, missing strdup
        tmp_node->item_name = item_name;
        tmp_node->price = price;
        tmp_node->quantity = quantity;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: id-532, omitted, codex, missing check for head == NULL
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
        // bug 2: id-531, omitted, approx-0.29, missing check for next == NULL
        tmp_node->next->next = tmp_node->next;
        // bug 3: id-531, omitted, approx-0.29, missing check for next == NULL
        tmp_node->next->next = tmp_node->next;
        free(tmp_node);
        // bug 4: id-530, omitted, human, missing free of item_name
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // swap the nodes at positions pos1 and pos2.
    // bug 1: id-698, omitted, approx-0.16, missing check for head == NULL
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
        // bug 2: id-697, omitted, approx-0.42, memory leak failing to update head
        // bug 3: id-699, present, approx-0.42, infinite loop, corrupted circular list
    }
    return EXIT_SUCCESS;
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


