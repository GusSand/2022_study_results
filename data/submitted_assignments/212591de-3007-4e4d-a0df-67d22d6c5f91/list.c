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
struct node {
    char* item_name;
    float price;
    int quantity;
    node* next;
};

node* getIndex(node* curr, int index) {
    if (curr == NULL)
        return 0;
    else if (index > 2) {
        return getIndex(curr->next, index - 1);
    } else {
        return curr;
    }
}

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
    if (head == NULL)
        return EXIT_FAILURE;
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
    int list_print_helper(node *head, int pos) {
        if (head == NULL) {
            return EXIT_SUCCESS;
        }
        char* str = malloc(sizeof(char)*MAX_ITEM_PRINT_LEN);
        list_item_to_string(head, str);
        printf("%d: %s\n", pos, str);
        return list_print_helper(head->next, pos+1);
    }
    return list_print_helper(head, 1);
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
    if (*head == NULL) {
        *head = malloc(sizeof(node));
        (*head)->item_name = item_name;
        (*head)->price = price;
        (*head)->quantity = quantity;
        (*head)->next = NULL;
        return EXIT_SUCCESS;
    }
    // if (pos == 0) {
    //     node* new_node = malloc(sizeof(node));
    //     new_node->item_name = item_name;
    //     new_node->price = price;
    //     new_node->quantity = quantity;
    //     new_node->next = *head;
    //     *head = new_node;
    //     return EXIT_SUCCESS;
    // }
    node* curr = *head;
    curr = getIndex(curr, pos);
    if (curr == NULL)
        return EXIT_FAILURE;
    node* newNode = malloc(sizeof(struct node));
    newNode->item_name = item_name;
    newNode->price = price;
    newNode->quantity = quantity;
    if (pos == 1) {
        newNode->next = *head;
        *head = newNode;
    } else {
        newNode->next = curr->next;
        curr->next = newNode;
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node* curr = *head;
    curr = getIndex(curr, pos);
    if (curr == NULL)
        return EXIT_FAILURE;
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{   
    node* curr = *head;
    curr = getIndex(curr, pos);
    if (curr == NULL)
        return EXIT_FAILURE;
    if (pos == 1) {
        *head = curr->next;
        free(curr);
    } else {
        node* toDelete = curr->next;
        printf("%s\n", toDelete->item_name);
        curr->next = toDelete->next;
        free(toDelete);
    }
    
    
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node* curr1 = getIndex(*head, pos1);
    node* curr2 = getIndex(*head, pos2);
    node* temp = NULL;
    if (pos1 == pos2)
        return EXIT_SUCCESS;
    temp = *head;
    if (pos1 == 1) {
        temp = *head;
        (*head) = curr2->next;
        curr2->next = temp;
        temp = curr2->next->next;
        curr2->next->next = (*head)->next;
        (*head)->next = temp;
    }
    else if (pos2 == 1) {
        temp = *head;
        (*head) = curr1->next;
        curr1->next = temp;
        temp = curr1->next->next;
        curr1->next->next = (*head)->next;
        (*head)->next = temp;
    } else {
        temp = curr1->next;
        curr1->next = curr2->next;
        curr2->next = temp;
        temp = curr1->next->next;
        curr1->next->next = curr2->next->next;
        curr2->next->next = temp;
    }

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    float max = head->price;
    int curr = 1;
    *pos = 1;
    while (head != NULL) {
        if(head->price > max) {
            *pos = curr;
            max = head->price;
        }
        ++curr;
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE* ptr;
    ptr = fopen(filename, "w");
    char str[MAX_ITEM_PRINT_LEN];
    if (ptr == NULL) {
        return EXIT_FAILURE;
    }
    while (head != NULL) {
        list_item_to_string(head, str);
        fprintf(ptr, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(ptr);
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

