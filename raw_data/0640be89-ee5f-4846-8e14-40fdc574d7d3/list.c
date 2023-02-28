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
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // if list is null or empty
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    // iterate through each node and print the info to stdout
    node *current = head;
    int pos = 0;
    char *str;
    while (current != NULL) {
        pos++;
        list_item_to_string(current, str);
        printf("%d: %s\n", pos, str);
        current = current->next;
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

    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;


    
    // If the position is 1, add item to the beginning of the list
    if(pos == 1)
    {
        node * newNode = malloc(sizeof(node));
        newNode->item_name = item_name;
        newNode->price = price;
        newNode->quantity = quantity;
        newNode->next = *head;
        *head = newNode;
    }
    // Otherwise, add item to the list at the given position
    else
    {
        node * current = *head;
        // Iterate through the list until the position is reached
        for(unsigned int i = 1; i < pos - 1; i++)
        {
            if(current->next == NULL)
                return EXIT_FAILURE;
            current = current->next;
        }

        // Create a new node to add to the list
        node * newNode = malloc(sizeof(node));
        newNode->item_name = item_name;
        newNode->price = price;
        newNode->quantity = quantity;
        newNode->next = current->next;
        current->next = newNode;
    }

    return EXIT_SUCCESS;
}


// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    
    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;

    // Iterate through the list until the position is reached
    node * current = *head;
    for(unsigned int i = 1; i < pos - 1; i++)
    {
        if(current->next == NULL)
            return EXIT_FAILURE;
        current = current->next;
    }

    // Update the item parameters
    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;

    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;

    // If the position is 1, remove the first node (and return its value)
    if(pos == 1)
    {
        node * removedNode = *head;
        *head = removedNode->next;
        free(removedNode);
    }
    // Otherwise, remove the node at the given position
    else
    {
        // Iterate through the list until the position is reached
        node * current = *head;
        node * prev = NULL;
        unsigned int i = 1;
        while(i < pos - 1)
        {
            i++;
            if(current->next == NULL)
                return EXIT_FAILURE;
            prev = current;
            current = current->next;
        }

        // Free the node at the given position
        node * removedNode = current->next;
        prev->next = removedNode->next;
        free(removedNode);
    }

    return EXIT_SUCCESS;
}


// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the positions are invalid, return EXIT_FAILURE
    if(pos1 < 1 || pos2 < 1 || pos1 == pos2)
        return EXIT_FAILURE;

    // Iterate through the list until the first position is reached
    node * first = *head;
    for(unsigned int i = 0; i < pos1 - 1; i++)
    {
        if(first->next == NULL)
            return EXIT_FAILURE;
        first = first->next;
    }

    // Iterate through the list until the second position is reached
    node * second = *head;
    for(unsigned int i = 0; i < pos2 - 1; i++){
        if(second->next == NULL)
            return EXIT_FAILURE;
        second = second->next;
    }

    // Swap first and second
    char* tempName = first->item_name;
    float tempPrice = first->price;
    int tempQuantity = first->quantity;
    first->item_name = second->item_name;
    first->quantity = second->quantity;
    first->price = second->price;
    second->item_name = tempName;
    second->price = tempPrice;
    second->quantity = tempQuantity;

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(head == NULL)
        return EXIT_FAILURE;

    int max = head->price;
    int maxPos = 1;
    int currentPos = 1;

    // Iterate through the list
    node * current = head;
    while (current != NULL) {
        //Check if current price is higher than max price
        if(current->price > max){
            max = current->price;
            maxPos = currentPos;
        }
        currentPos++;
        current = current->next;

    }

    *pos = maxPos;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(head == NULL)
        return EXIT_FAILURE;

    // Iterate through list
    node * current = head;
    while (current != NULL) {
        *total += current->price * current->quantity;
        current = current->next;
    }

    
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

    //Open file using given filename
    FILE * fptr = fopen(filename, "w");

    //check if opened correctly and if list is empty
    if(fptr == NULL || head == NULL)
        return EXIT_FAILURE;

    node * current = head;
    //iterate through and print to file
    while(current != NULL){
        fprintf(fptr, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }

    fclose(fptr);


    return EXIT_SUCCESS;
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
    //Open file using given filename
    FILE * fptr = fopen(filename, "r");

    //check if opened correctly
    if(fptr == NULL)
        return EXIT_FAILURE;

    list_init(head);
    char * line;
    char * name;
    char * price;
    char * quantity;
    unsigned int pos = 1;
    while(fgets(line, 100, fptr) != NULL){
        name = strtok(line, ",");
        price = strtok(NULL, ",");
        quantity = strtok(NULL, ",");
        list_add_item_at_pos(head, name, strtof(price, NULL), atoi(quantity), pos);
        pos = pos + 1;
    }
    fclose(fptr);
    return EXIT_SUCCESS;
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

