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
    // Print an item to the specified format
    // bug 1: id-188, omitted, human, missing check for str == NULL
    // bug 2: id-189, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-190, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 4: id-187, omitted, human, missing check for head == NULL
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);

    return EXIT_SUCCESS;
}

int list_print(node *head) {
    node* curr_node = head;
    int curr_pos = 1;
    while (curr_node != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        // bug 1: id-323, present, approx-0.49, doesn't check return value of list_item_to_string
        list_item_to_string(curr_node, item_str);
        // bug 2: id-324, omitted, approx-0.49, maybe uninit item_str
        printf("%d: %s\n", curr_pos, item_str);
        curr_pos++;
        curr_node = curr_node->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: id-51, omitted, human, missing check for head == NULL
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

    // bug 2: id-50, present, human, missing strdup
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

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: id-420, omitted, approx-0.31, missing check for head == NULL
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
    // bug 2: id-418, omitted, approx-0.06, missing free
    // bug 3: id-419, present, approx-0.06, missing strdup
    curr_node->item_name = item_name;
    curr_node->price = price;
    curr_node->quantity = quantity;

    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: id-529, omitted, codex, missing check for head == NULL
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

    // bug 2: id-528, omitted, codex, missing free of item_name
    free(curr_node);

    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // Choose the first node
    // bug 1: id-695, omitted, approx-0.17, missing check for head == NULL
    // bug 2: id-696, present, unknown, infinite loop from circular list
    // bug 3: id-694, present, unknown, losing elements of list
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

int list_find_highest_price_item_position(node *head, int *pos) {
    float max = -1.0;
    int curr_pos = 0;
    int max_pos = 0;

    // Iterating through the list determining max
    node* curr_node = head;

    // bug 1: id-616, omitted, human, missing check for pos == NULL
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
    // bug 1: id-656, omitted, human, missing check for total == NULL
    *total = sum;

    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // Open a file for writing
    // fp = fopen(filename, "w+");


    return EXIT_FAILURE;
}

int list_load(node **head, char *filename)
{
    // Load in from file
    return EXIT_FAILURE;
}

int list_deduplicate(node **head) 
{
    // bug 1: id-752, omitted, human, missing check for head == NULL
    node* curr_node = *head;

    // Iterate through the list
    while(curr_node != NULL) {
        curr_node = curr_node->next;
    }

    return EXIT_FAILURE;
}


