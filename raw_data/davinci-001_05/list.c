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
    // create a new node
    *head = malloc(sizeof(node));
    if (head == NULL) {
        fprintf(stderr, "list_init: malloc failed\n");
        return EXIT_FAILURE;
    }

    // set all node members to initial values
    (*head)->item_name = NULL;
    (*head)->price = 0;
    (*head)->quantity = 0;
    (*head)->next = NULL;

    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // check if node is null
    if (head == NULL) {
        fprintf(stderr, "list_item_to_string: node is null\n");
        return EXIT_FAILURE;
    }

    // check if string is null
    if (str == NULL) {
        fprintf(stderr, "list_item_to_string: string is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    char *item_name = head->item_name;
    float price = head->price;
    int quantity = head->quantity;

    // calculate length of string
    int length = strlen(item_name) + 18 + 2;

    // check if item name is empty
    if (item_name == NULL || strlen(item_name) == 0) {
        fprintf(stderr, "list_item_to_string: item_name is null or empty\n");
        return EXIT_FAILURE;
    }

    // check if price is less than 0
    if (price < 0) {
        fprintf(stderr, "list_item_to_string: price is negative\n");
        return EXIT_FAILURE;
    }

    // check if quantity is less than 0
    if (quantity < 0) {
        fprintf(stderr, "list_item_to_string: quantity is negative\n");
        return EXIT_FAILURE;
    }

    // check if length is greater than string length
    if (length > strlen(str)) {
        fprintf(stderr, "list_item_to_string: string not long enough\n");
        return EXIT_FAILURE;
    }

    // set up format string
    char format_str[length];
    sprintf(format_str, "%d * %s @ $%.2f ea", quantity, item_name, price);

    // copy string to buffer
    strncpy(str, format_str, strlen(format_str));

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
    // check if node is null
    if (head == NULL) {
        fprintf(stderr, "list_print: node is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    int pos = 1;
    node *current = head;
    while (current != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        list_item_to_string(current, item_str);
        printf("%d: %s\n", pos, item_str);

        pos++;
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
    // check if node is null
    if (head == NULL) {
        fprintf(stderr, "list_cost_sum: node is null\n");
        return EXIT_FAILURE;
    }

    // check if string is null
    if (total == NULL) {
        fprintf(stderr, "list_cost_sum: total is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    float sum = 0.0;
    node *current = head;
    while (current != NULL) {
        sum += current->price * current->quantity;
        current = current->next;
    }

    *total = sum;

    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    // check if node is null
    if (head == NULL) {
        fprintf(stderr, "list_save: node is null\n");
        return EXIT_FAILURE;
    }

    // check if string is null
    if (filename == NULL) {
        fprintf(stderr, "list_save: filename is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    int pos = 1;
    node *current = head;
    FILE *fp = fopen(filename, "w");
    while (current != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        list_item_to_string(current, item_str);
        fprintf(fp, "%s\n", item_str);

        pos++;
        current = current->next;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // check if node is null
    if (*head == NULL) {
        fprintf(stderr, "list_load: node is null\n");
        return EXIT_FAILURE;
    }

    // check if string is null
    if (filename == NULL) {
        fprintf(stderr, "list_load: filename is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp = fopen(filename, "r");
    if (fp == 0) {
        fprintf(stderr, "list_load: fopen failed\n");
        return EXIT_FAILURE;
    }

    // load the list
    while ((read = getline(&line, &len, fp)) != -1) {
        char *item_name = strtok(line, ",");
        float price = atof(strtok(NULL, ","));
        int quantity = atoi(strtok(NULL, "\n"));
        node *new_node = malloc(sizeof(node));
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = (*head);
        (*head) = new_node;
    }
    free(line);
    fclose(fp);

    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    // check if node is null
    if (*head == NULL) {
        fprintf(stderr, "list_deduplicate: node is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    node *current = *head;
    node *previous = NULL;
    while (current != NULL) {
        node *next = current->next;
        if (next != NULL && strcmp(current->item_name, next->item_name) == 0) {
            current->quantity += next->quantity;
            if (previous == NULL) {
                *head = next->next;
            } else {
                previous->next = next->next;
            }
            free(next);
        } else {
            previous = current;
        }
        current = next;
    }

    return EXIT_SUCCESS;
}
