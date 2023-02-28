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
    // Print an item to the specified format
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
    node* curr_node = head;
    int curr_pos = 1;
    while (curr_node != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        list_item_to_string(curr_node, item_str);
        printf("%d: %s\n", curr_pos, item_str);
        curr_pos++;
        curr_node = curr_node->next;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    node* prev_node = NULL;

    // Iterating through the list
    while (curr_node != NULL && curr_pos < pos)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
        curr_pos++;
    }

    // Create a new node
    node *item_node = (node *)malloc(sizeof(node));

    if (item_node == NULL)
    {
        printf("ERROR: malloc failed\n");
        return EXIT_FAILURE;
    }

    item_node->item_name = item_name;
    item_node->price = price;
    item_node->quantity = quantity;
    item_node->next = curr_node;

    // Add new node to the list
    if (prev_node == NULL) {
        *head = item_node;
    } else {
        prev_node->next = item_node;
    }
    item_node->next = curr_node;

    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // Iterate to the correct position
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    while (curr_node != NULL && curr_pos < pos)
    {
        curr_node = curr_node->next;
        curr_pos++;
    }

    if (curr_node == NULL)
    {
        printf("ERROR: Item not found\n");
        return EXIT_FAILURE;
    }

    // Update the item
    curr_node->item_name = item_name;
    curr_node->price = price;
    curr_node->quantity = quantity;

    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
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

    free(curr_node);

    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // Choose the first node
    unsigned int curr_pos = 1;
    node* curr_node = *head;
    node* prev_node = NULL;
    while (curr_node != NULL && curr_pos < pos1)
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

    // Choose the second node
    unsigned int curr_pos2 = 1;
    node* curr_node2 = *head;
    node* prev_node2 = NULL;
    while (curr_node2 != NULL && curr_pos2 < pos2)
    {
        prev_node2 = curr_node2;
        curr_node2 = curr_node2->next;
        curr_pos2++;
    }

    if (curr_node2 == NULL)
    {
        printf("ERROR: Item not found\n");
        return EXIT_FAILURE;
    }

    // Swap the nodes
    node* temp_node = curr_node->next;
    curr_node->next = curr_node2->next;
    curr_node2->next = temp_node;

    // Swap the remaining node
    if (prev_node == NULL) {
        *head = curr_node2;
    } else {
        prev_node->next = curr_node2;
    }

    if (prev_node2 == NULL) {
        *head = curr_node;
    } else {
        prev_node2->next = curr_node;
    }

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    float max = -1.0;
    int curr_pos = 0;
    int max_pos = 0;

    // Iterating through the list determining max
    node* curr_node = head;

    while(curr_node != NULL) {
        if(curr_node->price > max) {
            max = curr_node->price;
            max_pos = curr_pos;
        }
        curr_pos++;
        curr_node = curr_node->next;
    }

    // Update *pos
    *pos = curr_pos;

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    float sum = 0;
    
    // Iterate through the list
    node* curr_node = head;

    while(curr_node != NULL){
        float item_price = curr_node->price;
        int item_quantity = curr_node->quantity;

        sum += item_price*item_quantity;
        curr_node = curr_node->next;
    }

    // Updating total
    *total = sum;

    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // Open a file for writing
    // fp = fopen(filename, "w+");


    return EXIT_FAILURE;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // Load in from file
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    node* curr_node = *head;

    // Iterate through the list
    while(curr_node != NULL) {
        curr_node = curr_node->next;
    }

    return EXIT_FAILURE;
}

