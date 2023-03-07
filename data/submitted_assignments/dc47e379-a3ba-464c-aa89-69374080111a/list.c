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

    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);

    // char output[] = itoa(head->quantity) + " * " + head->item_name + " @ " + "$" + printf("%.2f", head->price) + " ea";
    // char output[100] = quantityStr + " * " + head->item_name;
    // char output[100] = strcat(quantityStr, " ");
    // str = strcat(quantityStr, " ");

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
    node *curr = head;
    int pos = 1;
    while (curr != NULL) {
      char itemAsString[100];
      list_item_to_string(curr, itemAsString);
      printf("%d: %s\n", pos, itemAsString);
      curr = curr->next;
      pos += 1;
    }
    return EXIT_SUCCESS;
}

// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 e
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
    node* newNode = (node*) malloc(sizeof(node));
    newNode->item_name = item_name;
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if(*head == NULL) {
        *head = newNode;
        return EXIT_SUCCESS;
    } else if (pos == 0) {
        newNode->next = *head;
        *head = newNode;
        return EXIT_SUCCESS;
    } else {
        node* prev = NULL;
        node* curr = *head;
        while (pos-1 > 0) {
            prev = curr;
            curr = curr->next;
            pos--;
        }
        prev->next = newNode;
        newNode->next = curr;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}


// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node* curr = *head;
    while (pos-1 > 0) {
        curr = curr->next;
        pos--;
    }
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(*head == NULL) {
        return EXIT_SUCCESS;
    } else if (pos == 1) {
        *head = (*head)->next;
        return EXIT_SUCCESS;
    } else {
        node* prev = NULL;
        node* curr = *head;
        while (pos-1 > 0) {
            prev = curr;
            curr = curr->next;
            pos--;
        }
        prev->next = curr->next;
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // find node at pos1, find node at pos2
    // swap the prev node to point to correct after swap
    // swap the node's next to appropriate node after swap

    node* pos1Prev;
    node* pos1Curr = *head;
    node* pos1Next;
    while (pos1-1 > 0) {
        pos1Prev = pos1Curr;
        pos1Curr = pos1Curr->next;
        pos1--;
    }

    node* pos2Prev;
    node* pos2Curr = *head;
    node* pos2Next;
    while (pos2-1 > 0) {
        pos2Prev = pos2Curr;
        pos2Curr = pos2Curr->next;
        pos2--;
    }

    if (*pos1Prev != NULL) {
        pos1Prev->next = pos2Curr;
    } else {
        *head = pos2Curr;
    }
    pos2Curr->next = pos1Next;

    pos2Prev->next = pos1Curr;
    pos1Curr->next = pos2Next;

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node* curr = *head;
    while (curr != NULL) {
      char itemAsString[100];
      list_item_to_string(curr, itemAsString);
      printf("%d: %s\n", pos, itemAsString);
      curr = curr->next;
      pos += 1;
    }

    return EXIT_FAILURE;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node* curr = *head;
    while (curr != NULL) {
      float price = curr->price;
      *total += price;
      curr = curr->next;
    }

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
    FILE *fptr = fopen(filename, "w");

    node* curr = *head;
    while (curr != NULL) {
      fprintf(fptr,"%s,%f,%d\n", curr->item_name, curr-> price, curr->quantity);
      curr = curr->next;
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
    FILE *fptr = fopen(filename, "r");

    node* curr = *head;
    while (curr != NULL) {
      curr = curr->next;
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fptr)) != -1) {
      char delim[] = ",";
      char *ptr = strtok(line, delim);
      // get three values, create new node, add to back of head
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

    // loop over the head note, create map of frequencies

    return EXIT_SUCCESS;
}

