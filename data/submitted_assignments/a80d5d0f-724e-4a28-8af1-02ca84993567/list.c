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
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
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
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        int pos = 1;
        while (cur != NULL) {
            printf("%d: %s\n", pos, list_item_to_string(cur, cur->item_name));
            cur = cur->next;
            pos++;
        }
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
    if (pos<1) {
        return EXIT_FAILURE;
    }
    if (*head == NULL) {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) {
            return EXIT_FAILURE;
        }
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = NULL;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    node *prev = NULL;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        prev = curr;
        curr = curr->next;
    }
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return EXIT_FAILURE;
    }
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = curr;
    if (curr == *head) {
        *head = new_node;
    } else {
        prev->next = new_node;
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (pos<1) {
        return EXIT_FAILURE;
    }
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = *head;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}


// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    if (pos<1) {
        return EXIT_FAILURE;
    }
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        node *curr = *head;
        *head = curr->next;
        free(curr);
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    node *prev = NULL;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr);
    return EXIT_SUCCESS;
}


// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (pos1 < 1 || pos2 < 1) {
        return EXIT_FAILURE;
    }
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    for (unsigned int i=1; i<pos1; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    list_update_item_at_pos(head, curr->item_name, curr->price, curr->quantity, pos2);
    node *curr2 = *head;
    

    for (unsigned int i=1; i<pos2; i++) {
        if (curr2 == NULL) {
            return EXIT_FAILURE;
        }
        curr2 = curr2->next;
    }
    list_update_item_at_pos(head, curr2->item_name, curr2->price, curr2->quantity, pos1);
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        int curr_pos  = 1 ; 
        int max = -1; 
        while (cur != NULL) {
            if (cur->price > max) {
                max = cur->price; 
                pos = curr_pos; 
                }
            cur = cur->next;
            curr_pos++;
        }
    }
    return EXIT_SUCCESS;
    
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total){
    
        return EXIT_SUCCESS; 

}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    return EXIT_SUCCESS; 
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate 

    return EXIT_SUCCESS;
}

