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

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS
// to indicate whether the operation was successful or not.

// Members of the node struct:
// char* item_name, float price, int quantity, node *next

// create a new list
int list_init(node **head) {
    // check for NULL pointer
    if (head == NULL) return EXIT_FAILURE;

    // initialize the first node
    *head = (node *)malloc(sizeof(node));
    if (*head == NULL) return EXIT_FAILURE;

    // initialize the first node
    (*head)->item_name = NULL;
    (*head)->price = 0.0;
    (*head)->quantity = 0;
    (*head)->next = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // check for NULL pointer
    if (head == NULL || str == NULL) return EXIT_FAILURE;

    // check for empty list
    if (head->item_name == NULL) return EXIT_SUCCESS;

    // print item_name
    char item_name[MAX_ITEM_PRINT_LEN + 1];
    strncpy(item_name, head->item_name, MAX_ITEM_PRINT_LEN);
    item_name[MAX_ITEM_PRINT_LEN] = '\0';

    // print price
    char price[20];
    sprintf(price, "%.2f", head->price);

    // print quantity
    char quantity[20];
    sprintf(quantity, "%d", head->quantity);

    // print string
    char format[] = "%d * %s @ $%s ea";
    int result = snprintf(str, MAX_ITEM_PRINT_LEN, format, quantity, item_name, price);
    if (result < 0) return EXIT_FAILURE;

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
    // check for NULL pointer
    if (head == NULL) return EXIT_FAILURE;

    // check for empty list
    if (head->item_name == NULL) return EXIT_SUCCESS;

    // print list until last node
    int pos = 0;
    node *current = head;
    while (current->next != NULL) {
        char str[MAX_ITEM_PRINT_LEN + 1];
        list_item_to_string(current, str);
        printf("%d: %s\n", pos, str);
        current = current->next;
        pos++;
    }

    // print last node
    char str[MAX_ITEM_PRINT_LEN + 1];
    list_item_to_string(current, str);
    printf("%d: %s\n", pos, str);

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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    // check for NULL pointer
    if (head == NULL || total == NULL) return EXIT_FAILURE;

    // check for empty list
    if (head->item_name == NULL) return EXIT_SUCCESS;

    // initialize total_cost
    float total_cost = 0.0;

    // calculate total_cost
    node *current = head;
    while (current->next != NULL) {
        total_cost += current->price * current->quantity;
        current = current->next;
    }
    total_cost += current->price * current->quantity;

    *total = total_cost;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    // check for NULL pointer
    if (head == NULL || filename == NULL) return EXIT_FAILURE;

    // check for empty list
    if (head->item_name == NULL) return EXIT_SUCCESS;

    FILE *file = fopen(filename, "w");
    if (file == NULL) return EXIT_FAILURE;

    // save list to file
    node *current = head;
    while (current->next != NULL) {
        fprintf(file, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }
    fprintf(file, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);

    fclose(file);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // check for NULL pointer
    if (head == NULL || filename == NULL) return EXIT_FAILURE;

    // check for empty list
    if (*head == NULL || (*head)->item_name == NULL) return EXIT_SUCCESS;

    FILE *file = fopen(filename, "r");
    if (file == NULL) return EXIT_FAILURE;

    // load list from file
    node *current = *head;
    while (fscanf(file, "%s,%f,%d", current->item_name, &current->price, &current->quantity) != EOF) {
        current->next = (node *)malloc(sizeof(node));
        if (current->next == NULL) return EXIT_FAILURE;
        current = current->next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    // check for NULL pointer
    if (head == NULL) return EXIT_FAILURE;

    // check for empty list
    if (*head == NULL) return EXIT_SUCCESS;

    node *current = *head;
    node *previous = NULL;
    while (current != NULL) {
        node *next = current->next;
        while (next != NULL) {
            if (strcmp(current->item_name, next->item_name) == 0) {
                current->price += next->price;
                current->quantity += next->quantity;
                current->next = next->next;
                free(next);
                next = current->next;
            } else {
                previous = current;
                current = next;
                next = next->next;
            }
        }
        previous = current;
        current = current->next;
    }

    return EXIT_SUCCESS;
}
