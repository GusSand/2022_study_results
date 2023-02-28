#include <stdio.h> 
#include <stdlib.h>
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
    if(head == NULL){
        return EXIT_FAILURE;
    }
    else{
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    int pos = 1;
    while(head != NULL){
        printf("%d: %d * %s @ $%.2f ea\n", pos, head->quantity, head->item_name, head->price);
        pos++;
        head = head->next;
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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(*head == NULL || pos > sizeof(*head)){
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            node *temp = (*head)->next;

            node *new_node = malloc(sizeof(node));

            new_node->item_name = item_name;
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = temp;
            (*head)->next = new_node;
            return EXIT_SUCCESS;
        }
        currPos++;
        *head = (*head)->next;
    }
    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            strcpy((*head)->item_name, item_name);
            (*head)->price = price;
            (*head)->quantity = quantity;
            return EXIT_SUCCESS;
        }
        currPos++;
        *head = (*head)->next;
    }
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            node *node_to_remove = *head;
            *head = (*head)->next;
            free(node_to_remove);
            return EXIT_SUCCESS;
        }
        currPos++;
        *head = (*head)->next;
    }
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (*head == NULL || pos1 == pos2 || pos1 > sizeof(*head) || pos2 > sizeof(*head))
    {
        return EXIT_FAILURE;
    }
    
    node *item_to_swap1;
    node *item_to_swap2;
    node *temp;
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos1){
            item_to_swap1 = *head;
        }
        else if(currPos == pos2){
            item_to_swap2 = *head;
        }
        currPos++;
        *head = (*head)->next;
    }
    temp = item_to_swap1;
    item_to_swap1 = item_to_swap2;
    item_to_swap2 = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    int max = head->price;
    while(head != NULL){
        if(head->price > max){
            max = head->price;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{ 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    while(head != NULL){
        *total += (head->price * head->quantity);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    FILE *file = fopen(filename, "w");
    while(head != NULL){
        fprintf(file, "%s,$%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        return EXIT_FAILURE;
    }
    char data[MAX_ITEM_PRINT_LEN];
    char* token;
    float num;
    int quantity;
    while(fgets(data, MAX_ITEM_PRINT_LEN, file) != NULL){
        node *newNode = malloc(sizeof(node));
        sscanf(data, "%s,%f,%d", newNode->item_name, &num, &quantity);
        newNode->price = num;
        newNode->quantity = quantity;
        newNode->next = NULL;
        if(*head == NULL){
            *head = newNode;
        }
        else{
            (*head)->next = newNode;
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    node *currNode = *head;
    while(currNode != NULL){
        node *itemPtr = currNode->next;
        while(itemPtr != NULL){
            if(strcmp(currNode->item_name, itemPtr->item_name) == 0){
                currNode->quantity += itemPtr->quantity;
                currNode->next = itemPtr->next;
                free(itemPtr);
                itemPtr = currNode->next;
            }
            else{
                itemPtr = itemPtr->next;
            }
        }
        currNode = currNode->next;
    }
    return EXIT_SUCCESS;
}

