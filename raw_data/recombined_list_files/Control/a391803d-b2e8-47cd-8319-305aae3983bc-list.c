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

// Auxiliary functions

node* find_prev_node(node* head, char* item_name, int pos) {
    node *curr = head;
    int i = 1;
    while (i < pos) {
        // bug 2: missing check for item_name == NULL
        if (strcmp(curr->item_name, item_name) == 0)
            return curr;    // node with the same item_name!
        // bug 3: missing check for next == NULL
        curr = curr->next;
        i++;
    }
    return NULL;
}

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        printf("Need a node!\n");
        return EXIT_FAILURE;
    }
    sprintf(str, "%i * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for total == NULL
    *total = 0;
    node *curr = head;

    // go through list
    while (curr != NULL) {
        (*total) += curr->price * curr->quantity;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    
    // open file for writing
    node *curr = head;
    // bug 1: missing check for filename == NULL
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening the file %s\n", filename);
        return EXIT_FAILURE;
    }
    while (curr != NULL) {
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(fp, "%s,%.2f,%i\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node *curr = *head;
    node *prev = NULL;
    // bug 2: missing check for filename == NULL
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
    // bug 3: use of uninitialized item_name
    char *item_name;
    float price;
    int quantity;
    // read the lines and load the nodes at the end of the list
    // bug 4: fscanf may not initialize price, quantity
    while (fscanf(fp, "%s,%.2f,%i\n", item_name, price, quantity) != EOF) {
        node *newNode = (node *)malloc(sizeof(node));
        // bug 5: use of uninitialized newNode->item_name
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

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
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
            // bug 4: missing free of item_name
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


