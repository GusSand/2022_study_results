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
    if (!head) return EXIT_FAILURE;
    if (!str) return EXIT_FAILURE;
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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL)
        return EXIT_FAILURE;
    struct _node *curr = head;
    int pos = 0;
    while (curr != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        list_item_to_string(curr, item_str);
        printf("%d: %s\n", pos++, item_str);
        curr = curr->next;
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if (pos == 0) {
        node *temp = (node *) malloc(sizeof(node));
        temp->next = (*head);
        (*head) = temp;
        temp->quantity = quantity;
        strncpy(temp->item_name, item_name, MAX_ITEM_PRINT_LEN);
        temp->price = price;
        return EXIT_SUCCESS;
    }

    struct _node *curr = *head;
    struct _node *prev = NULL;
    int i = 0;

    while (curr != NULL && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    else {
        node *temp = (node *) malloc(sizeof(node));
        temp->next = curr;
        prev->next = temp;
        temp->quantity = quantity;
        strncpy(temp->item_name, item_name, MAX_ITEM_PRINT_LEN);
        temp->price = price;
        return EXIT_SUCCESS;
    }
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (pos == 0) {
        (*head)->quantity = quantity;
        strncpy((*head)->item_name, item_name, MAX_ITEM_PRINT_LEN);
        (*head)->price = price;
        return EXIT_SUCCESS;
    }

    struct _node *curr = *head;
    int i = 0;

    while (curr != NULL && i < pos) {
        curr = curr->next;
        i++;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    else {
        curr->quantity = quantity;
        strncpy(curr->item_name, item_name, MAX_ITEM_PRINT_LEN);
        curr->price = price;
        return EXIT_SUCCESS;
    }
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) return EXIT_FAILURE;
    int i = 0, max_i = 0, max_price = 0;
    while (head != NULL) {
        if (head->price > max_price) {
            max_i = i;
            max_price = head->price;
        }
        head = head->next;
        i++;
    }
    *pos = max_i;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) return EXIT_FAILURE;
    float sum = 0;
    while (head != NULL) {
        sum += head->price * head->quantity;
        head = head->next;
    }
    *total = sum;
    return EXIT_SUCCESS;
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

