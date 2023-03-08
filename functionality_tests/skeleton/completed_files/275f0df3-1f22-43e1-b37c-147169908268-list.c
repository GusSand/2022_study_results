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
    str = head->quantity;
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
    node* curr = head;
    int count = 0;
    while (curr != NULL) {
    count++;
    printf('%d /n', count);
    printf('%s /n', head->item_name);
    printf('%d /n', head->price);
    curr = curr->next;
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
    node new = {
        .item_name = item_name,
        .price = price,
        .quantity = quantity
    };

    int count = 0;
    node* prev = head;
    head = *head->next;
    while (head != NULL && count != pos) {
        head = *head->next;
        prev = prev->next;
        count++;
    }
    prev->next = new;
    new->next = head;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    int count = 0;
    while (head != NULL && count != pos) {
        head = *head->next;
        count++;
    }
    *head->item_name = item_name;
    *head->price = item_price;
    *head->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{   node * prev = head;
    head = *head->next;
    int count = 0;
    while (head != NULL && count != pos) {
        head = *head->next;
        prev = prev->next;
        count++;
    }
    prev->next = *head->next;
    *head->next = NULL;
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    int count1 = 0;
    int count2 = 0;
    node* first = head;
    node* sec = head;
    node* temp = head;
    while (count1 != pos1) {
        first = first->next;
        count1++;
    }

    while (count2 != pos2) {
        sec = sec->next;
        count2++;
    }

    temp = first;
    first = sec;
    sec = temp;
    temp = NULL;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    int max_price = - 1;
    int max_price_pos = 0;
    int count = 0;
    while (head != NULL) {
        count++;
        if (head->price > max_price) {
            max_price = head->price;
            max_price_pos = count;
        }
    }
    pos = max_price_pos;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    float total = 0;
    while (head != NULL) {
        total += *head->price * head->quantity;
    }

    return EXIT_SUCCESS;
}
