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
// successful or not.

// implement a node struct with item, quantity, price
// struct node {
//   char* item;
//   int quantity;
//   int price;
//   struct node *next;
// };

// create a new list
int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

// print the list to stdout
// This should be in the format of:
// "pos: quantity * item_name @ $price ea", where 
//   pos is the position of the item in the list, 
//   item_name is the item_name of the item and 
//   price is the float price of the item formatted with 2 decimal places.
// For example:
// """1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// 3: 4 * apple @ $3.00 ea
// """
// It should return a newline character at the end of each item. 
// It should not have a leading newline character.
int list_print(node *head) {
    // TODO: Implement this function,
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *cur = head;
    int pos = 1;
    char *str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
    while (cur != NULL) {
        list_item_to_string(cur, str);
        printf("%d: %s\n", pos, str);
        pos++;
        free(str);
        cur = cur->next;
    }
    return EXIT_SUCCESS;
}

// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 2 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // if the head is NULL, add the node at the first position
    if (*head == NULL) {
        node *new = malloc(sizeof(node));
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
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = cur->next;
    cur->next = new_node;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // if the list is empty, reutrn failure
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
    // free(cur->item_name);
    cur->item_name = strdup(item_name);
    // cur->item_name = item_name;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // if the list is empty, return fail
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // if the node to be removed is at position 1, set the head->next to be the head
    if (pos == 1) {
        node *new_head = (*head)->next;
        free(*head);
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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // if the list is empty, return fail
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

    node1->next = node2->next;
    // connect previous nodes to node 1 and 2
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // if the list is empty, return fail
    if 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

