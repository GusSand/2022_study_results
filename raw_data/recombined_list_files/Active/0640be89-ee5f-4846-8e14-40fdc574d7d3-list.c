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
    // bug 1: id-141, omitted, approx-0.06, missing check for str == NULL
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // bug 2: id-143, present, approx-0.06, Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 3: id-142, omitted, approx-0.06, does not check if str is NULL before print
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

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
    // bug 1: id-294, omitted, human, doesn't initialize temporary char* buf
    while (current != NULL) {
        pos++;
        // bug 2: id-293, present, human, doesn't check return value of list_item_to_string
        list_item_to_string(current, str);
        printf("%d: %s\n", pos, str);
        current = current->next;
    }
    
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;

    // bug 2: id-4, omitted, codex, missing check for head == NULL

    // If the position is 1, add item to the beginning of the list
    if(pos == 1)
    {
        node * newNode = malloc(sizeof(node));
        // bug 1: id-3, present, codex, missing strdup
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
        // bug 3: id-3, present, approx-0.50, missing strdup
        newNode->item_name = item_name;
        newNode->price = price;
        newNode->quantity = quantity;
        newNode->next = current->next;
        current->next = newNode;
    }

    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: id-383, omitted, codex, missing check for head == NULL
    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;

    // Iterate through the list until the position is reached
    node * current = *head;
    // bug 2: id-384, omitted, codex, missing check for *head == NULL
    for(unsigned int i = 1; i < pos - 1; i++)
    {
        if(current->next == NULL)
            return EXIT_FAILURE;
        current = current->next;
    }

    // Update the item parameters
    // bug 3: id-381, omitted, approx-0.04, missing free
    // bug 4: id-382, present, approx-0.04, missing strdup
    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;

    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the position is invalid, return EXIT_FAILURE
    if(pos < 1)
        return EXIT_FAILURE;

    // bug 1: id-501, omitted, human, missing check for head == NULL
    // If the position is 1, remove the first node (and return its value)
    if(pos == 1)
    {
        node * removedNode = *head;
        *head = removedNode->next;
        // bug 2: id-500, omitted, human, missing free on item_name
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
        // bug 3: id-500, omitted, codex, missing free on item_name
        free(removedNode);
    }

    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // If the positions are invalid, return EXIT_FAILURE
    if(pos1 < 1 || pos2 < 1 || pos1 == pos2)
        return EXIT_FAILURE;

    // bug 1: id-676, omitted, approx-0.05, missing check for head == NULL
    // bug 2: id-677, omitted, approx-0.05, missing check for *head == NULL
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

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(head == NULL)
        return EXIT_FAILURE;

    // bug 2: id-599, present, human, int vs float confusion
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

    // bug 1: id-598, omitted, human, missing check for pos == NULL
    *pos = maxPos;
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(head == NULL)
        return EXIT_FAILURE;

    // Iterate through list
    node * current = head;
    while (current != NULL) {
        // bug 1: id-646, omitted, human, missing check for total == NULL
        *total += current->price * current->quantity;
        current = current->next;
    }

    
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    //Open file using given filename
    // bug 1: id-793, omitted, human, missing check for filename == NULL
    FILE * fptr = fopen(filename, "w");

    //check if opened correctly and if list is empty
    // bug 2: id-792, omitted, human, leaks file descriptor on EXIT_FAILURE
    if(fptr == NULL || head == NULL)
        return EXIT_FAILURE;

    node * current = head;
    //iterate through and print to file
    while(current != NULL){
        // bug 3: id-791, present, human, missing check for fprintf failure
        // bug 4: id-794, omitted, human, missing check for item_name == NULL
        fprintf(fptr, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }

    fclose(fptr);


    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //Open file using given filename
    // bug 1: id-877, omitted, human, missing check for filename == NULL
    FILE * fptr = fopen(filename, "r");

    //check if opened correctly
    if(fptr == NULL)
        return EXIT_FAILURE;

    // bug 2: id-875, present, human, memory leak overwriting head ptr
    list_init(head);
    char * line;
    char * name;
    char * price;
    char * quantity;
    unsigned int pos = 1;
    // bug 3: id-876, present, human, use of uninitialized char * line
    while(fgets(line, 100, fptr) != NULL){
        // bug 4: id-878, present, human, fail to check if strtok returns NULL
        name = strtok(line, ",");
        price = strtok(NULL, ",");
        quantity = strtok(NULL, ",");
        // bug 5: id-874, present, human, missing check of return status for list_add_item_at_pos
        list_add_item_at_pos(head, name, strtof(price, NULL), atoi(quantity), pos);
        pos = pos + 1;
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}


