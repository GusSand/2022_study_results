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

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS
// to indicate whether the operation was successful or not.

// Members of the node struct:
// char* item_name, float price, int quantity, node *next

// create a new list
int list_init(node **head) {
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    char item_name[MAX_ITEM_PRINT_LEN];
    char price[MAX_ITEM_PRINT_LEN];
    char quantity[MAX_ITEM_PRINT_LEN];
    char *ret_str;
    int num_char;
    
    if (head == NULL) return EXIT_FAILURE;
    
    // extract the item name
    ret_str = strstr(head->item_name, " ");
    if (ret_str == NULL) return EXIT_FAILURE;
    
    num_char = ret_str - head->item_name;
    if (num_char >= MAX_ITEM_PRINT_LEN) return EXIT_FAILURE;
    
    strncpy(item_name, head->item_name, num_char);
    item_name[num_char] = '\0';
    
    // extract the price
    sprintf(price, "%.2f", head->price);
    
    // extract the quantity
    sprintf(quantity, "%d", head->quantity);
    
    sprintf(str, "%s %s @ $%s ea", quantity, item_name, price);
    
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
    node *curr = head;
    int i = 0;
    char item_str[MAX_ITEM_PRINT_LEN];
    
    while (curr != NULL) {
        i++;
        list_item_to_string(curr, item_str);
        printf("%d: %s\n", i, item_str);
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node *curr, *new_node;
    int i;
    
    // check for invalid inputs
    if (head == NULL || item_name == NULL || quantity <= 0) return EXIT_FAILURE;
    
    // check if the list is empty
    if (*head == NULL) {
        *head = malloc(sizeof(node));
        (*head)->item_name = item_name;
        (*head)->price = price;
        (*head)->quantity = quantity;
        (*head)->next = NULL;
        return EXIT_SUCCESS;
    }
    
    // check if the position is past the size of the list
    if (pos == 0) {
        new_node = malloc(sizeof(node));
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    
    curr = *head;
    for (i = 1; i < pos; i++) {
        if (curr->next == NULL) return EXIT_FAILURE;
        curr = curr->next;
    }
    
    new_node = malloc(sizeof(node));
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = curr->next;
    curr->next = new_node;
    
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node *curr;
    int i;
    
    // check for invalid inputs
    if (head == NULL || item_name == NULL || quantity <= 0) return EXIT_FAILURE;
    
    // check if the list is empty
    if (*head == NULL) return EXIT_FAILURE;
    
    curr = *head;
    for (i = 1; i < pos; i++) {
        if (curr->next == NULL) return EXIT_FAILURE;
        curr = curr->next;
    }
    
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    node *curr, *prev;
    int i;
    
    // check for invalid inputs
    if (head == NULL) return EXIT_FAILURE;
    
    // check if the list is empty
    if (*head == NULL) return EXIT_FAILURE;
    
    // check if the position is past the size of the list
    if (pos == 0) {
        curr = *head;
        *head = curr->next;
        free(curr);
        return EXIT_SUCCESS;
    }
    
    curr = *head;
    for (i = 1; i < pos; i++) {
        if (curr->next == NULL) return EXIT_FAILURE;
        prev = curr;
        curr = curr->next;
    }
    
    prev->next = curr->next;
    free(curr);
    
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node *curr1, *curr2, *prev1, *prev2;
    int i;
    
    // check for invalid inputs
    if (head == NULL) return EXIT_FAILURE;
    
    // check if the list is empty
    if (*head == NULL) return EXIT_FAILURE;
    
    // check if the position is past the size of the list
    if (pos1 == 0 || pos2 == 0) return EXIT_FAILURE;
    
    if (pos1 == pos2) return EXIT_SUCCESS;
    
    curr1 = *head;
    for (i = 1; i < pos1; i++) {
        if (curr1->next == NULL) return EXIT_FAILURE;
        prev1 = curr1;
        curr1 = curr1->next;
    }
    
    curr2 = *head;
    for (i = 1; i < pos2; i++) {
        if (curr2->next == NULL) return EXIT_FAILURE;
        prev2 = curr2;
        curr2 = curr2->next;
    }
    
    prev1->next = curr2;
    prev2->next = curr1;
    curr1->next = curr2->next;
    curr2->next = curr1->next;
    curr1->next = curr2;
    
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    node *curr;
    int i, highest_price_pos = 0;
    float highest_price = 0;
    
    // check for invalid inputs
    if (head == NULL || pos == NULL) return EXIT_FAILURE;
    
    // check if the list is empty
    if (head == NULL) return EXIT_FAILURE;
    
    curr = head;
    for (i = 0; curr != NULL; curr = curr->next, i++) {
        if (curr->price > highest_price) {
            highest_price = curr->price;
            highest_price_pos = i;
        }
    }
    
    *pos = highest_price_pos;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    node *curr;
    int i;
    float sum = 0;
    
    // check for invalid inputs
    if (head == NULL || total == NULL) return EXIT_FAILURE;
    
    // check if the list is empty
    if (head == NULL) return EXIT_FAILURE;
    
    curr = head;
    for (i = 0; curr!= NULL; curr = curr->next, i++) {
        sum += curr->price*curr->quantity;
    }
    
    *total = sum;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    node *curr;
    FILE *fp;
    int i;
    
    // check for invalid inputs
    if (head == NULL || filename == NULL) return EXIT_FAILURE;
    
    // check if the list is empty
    if (head == NULL) return EXIT_FAILURE;
    
    // open the file for writing
    fp = fopen(filename, "w");
    if (fp == NULL) return EXIT_FAILURE;
    
    curr = head;
    for (i = 0; curr!= NULL; curr = curr->next, i++) {
        fprintf(fp, "%s,%.2f,%d\n", curr->item_name, curr->price, curr->quantity);
    }
    
    fclose(fp);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}
