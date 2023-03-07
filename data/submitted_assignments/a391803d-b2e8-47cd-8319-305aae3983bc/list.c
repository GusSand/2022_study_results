#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"

// NOTE: I was unable to test this file according to the instructions in
// README.md!

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
        printf("Need a node!\n");
        return EXIT_FAILURE;
    }
    sprintf(str, "%i * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
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
    if (curr == NULL) {
        print("Need to pass in a singly linked list!\n");
        return EXIT_FAILURE;
    }
    while (curr != NULL) {
        printf("%i: %i * %s @ $%.2f ea\n", pos, head->quantity, head->item_name, head->price);
        curr = curr->next;
        pos++;
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
    node *curr = *head;
    node *prev = NULL;
    // allocate a new node on the heap
    node *newNode = (node *)malloc(sizeof(node));
    sprintf(newNode->item_name, "%s", item_name);
    newNode->price=price;
    newNode->quantity=quantity;
    newNode->next=NULL;
    int i = 1;

    // search for the node    
    while (i < pos) {
        if (curr == NULL) {
            printf("pos is out of range: There is not enough items!\n")
            return EXIT_FAILURE;    // Out of range: There is not enough items
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    prev->next = newNode;
    newNode->next = curr;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = *head;
    node *prev = NULL;
    int i = 1;
    
    while (i < pos) {
        if (curr == NULL) {
            printf("pos is out of range: There is not enough items!\n")
            return EXIT_FAILURE;    // Out of range: There is not enough items
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (curr == NULL) {
        // allocate on heap and point to newNode
        node *newNode = (node *)malloc(sizeof(node));
        newNode->next = NULL;
        prev->next = newNode;
        curr = newNode;
    }
    // update the node
    sprintf(curr->item_name, "%s", item_name);
    curr->price = price;
    curr->quantity = quantity;

    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = *head;
    node *prev = NULL;
    int i = 1;
    
    // search for the node
    while (i < pos) {
        if (curr == NULL) {
            printf("pos is out of range: There is not enough items!\n")
            return EXIT_FAILURE;    // Out of range: There is not enough items
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    if (curr == NULL)
        return EXIT_SUCCESS;
    
    prev->next = curr->next;
    free(curr);
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr1 = *head;
    node *prev1 = NULL;
    int i1 = 1;
    node *curr2 = *head;
    node *prev2 = NULL;
    int i2 = 1;
    
    // search for the 2 nodes
    while (i1 < pos1) {
        if (curr == NULL) {
            printf("pos1 is out of range: There is not enough items!\n")
            return EXIT_FAILURE;    // Out of range: There is not enough items
        }
        prev1 = curr1;
        curr1 = curr1->next;
        i1++;
    }
    while (i2 < pos2) {
        if (curr == NULL) {
            printf("pos is out of range: There is not enough items!\n")
            return EXIT_FAILURE;    // Out of range: There is not enough items
        }
        prev2 = curr2;
        curr2 = curr2->next;
        i2++;
    }

    // swap
    if ((curr1 == NULL) || (curr2 == NULL)) {
        printf("At least one of the positions does not have an item!\n");
        return EXIT_FAILURE;        // Nothing is done/changed: success
    }
    prev1->next=curr2;
    prev2->next=curr1;

    node *temp = curr2->next;
    curr2->next = curr1->next;  //change curr2->next
    curr1->next = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // alter *pos
    node *curr = head;
    int i = 1;
    int highest_price = 0;
    *pos = 1;

    if (curr == NULL) {
        *pos = 0;
        printf("Need to pass in a singly linked list with items!\n")
        return EXIT_FAILURE;
    }
    // go through list
    while (curr != NULL) {
        if (highest_price < curr->price) {
            highest_price = curr->price;
            *pos = i;
        }
        curr = curr->next;
        i++;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    *total = 0;
    node *curr = head;

    // go through list
    while (curr != NULL) {
        (*total) += curr->price * curr->quantity;
        curr = curr->next;
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
    
    // open file for writing
    node *curr = head;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening the file %s\n", filename);
        return EXIT_FAILURE;
    }
    while (curr != NULL) {
        fprintf(fp, "%s,%.2f,%i\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }
    fclose(fp);
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
    node *curr = *head;
    node *prev = NULL;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file %s\n", filename);
        return EXIT_FAILURE;
    }
    // go to the end of the list
    if (curr == NULL) {
        printf("Need to pass in a singly linked list!\n");
        return EXIT_FAILURE;    // need to pass in a singly linked list!
    }
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }
    curr = prev;    // last item of list
    char *item_name;
    float price;
    int quantity;
    // read the lines and load the nodes at the end of the list
    while (fscanf(fp, "%s,%.2f,%i\n", item_name, price, quantity) != EOF) {
        node *newNode = (node *)malloc(sizeof(node));
        sprintf(newNode->item_name, "%s", item_name);
        newNode->price = price;
        newNode->quantity = quantity;
        newNode->next = NULL;
        curr->next = newNode;
        curr = curr->next;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

// Return the node* with the item_name before pos or NULL
node* find_prev_node(node* head, char* item_name, int pos) {
    node *curr = head;
    int i = 1;
    while (i < pos) {
        if (strcmp(curr->item_name, item_name) == 0)
            return curr;    // node with the same item_name!
        curr = curr->next;
        i++;
    }
    return NULL;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = *head;
    node *prev = NULL;
    node *orig_name = NULL;
    node *temp = NULL;
    int pos = 1;
    if (curr == NULL) {
        printf("Need to pass in a singly linked list!\n");
        return EXIT_FAILURE;
    }
    prev = curr;
    curr = curr->next;
    // go through the list
    while (curr != NULL) {
        orig_name = find_prev_node(head, curr->item_name, pos);
        if (orig_name != NULL) {
            orig_name->quantity += curr->quantity;
            temp = curr;
            curr = curr->next;
            prev->next = curr;
            free(temp);
        }
        else {
            prev = curr;
            curr = curr->next;
            pos++;
        }
    }
    return EXIT_SUCCESS;
}

