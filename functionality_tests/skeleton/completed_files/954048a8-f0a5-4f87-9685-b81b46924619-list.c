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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        str = "";
        return EXIT_FAILURE;
    }
    node *current = head;
    while (current != NULL) {
        sprintf(str, "%d * %s @ $%.2f ea", current->quantity, current->item_name, current->price);
        current = current->next;
    }
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
    if (head == NULL) {
        printf("\n");
        return EXIT_FAILURE;
    }
    node *current = head;
    int pos = 1;
    while (current != NULL) {
        printf("%d: %d * %s @ $%.2f ea\n", pos, current->quantity, current->item_name, current->price);
        current = current->next;
        pos++;
    }
    return EXIT_SUCCESS;

}


// insert a new item before the specified position
// (1 = first item, 2 = second item, etc)
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
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    if(pos == 1){
        node *new_node = malloc(sizeof(node));
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = current;
        *head = new_node;
    }else{
        int i;
        for (i = 1; i < (pos - 1); i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        node *new_node = malloc(sizeof(node));
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = current->next;
        current->next = new_node;
    }
    return EXIT_SUCCESS;

}


// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    if(pos == 1){
        current->item_name = item_name;
        current->price = price;
        current->quantity = quantity;
    }else{
        int i;
        for (i = 1; i < pos; i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        current->item_name = item_name;
        current->price = price;
        current->quantity = quantity;
    }
    return EXIT_SUCCESS;
}


// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    if(pos == 1){
        *head = current->next;
        free(current);
    }else{
        int i;
        for (i = 1; i < (pos - 1); i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        node *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    return EXIT_SUCCESS;
}


// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    node *current = *head;
    node *current1 = current;
    node *current2 = current;
    int i;
    for (i = 1; i < pos1; i++){
        if(current->next == NULL){
            break;
        }
        current = current->next;
    }
    current1 = current->next;
    for (i = 1; i < pos2; i++){
        if(current->next == NULL){
            break;
        }
        current = current->next;
    }
    current2 = current->next;
    current->next = current2;
    current2->next = current1;
    current1->next = current2->next;
    return EXIT_SUCCESS;
}
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == NULL){
        return EXIT_FAILURE;
    }
    if(head->next == NULL){
        *pos = 1;
        return EXIT_SUCCESS;
    }
    node *current = head;
    int i = 1;
    float max = 0.0;
    while (current != NULL) {
        if(current->price > max){
            max = current->price;
            *pos = i;
        }
        current = current->next;
        i++;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if()
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
    if(head!=NULL){
        
        return EXIT_SUCCESS;
    }
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
