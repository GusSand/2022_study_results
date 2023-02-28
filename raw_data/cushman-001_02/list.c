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
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // check the head and the item_name
    if (head == NULL || head->item_name == NULL) {
        return EXIT_FAILURE;
    }
    int len = snprintf(str, MAX_ITEM_PRINT_LEN, "%i * %s @ $%.2f ea", 
                       head->quantity, head->item_name, head->price);
    if (len < 0) {
        return EXIT_FAILURE;
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
    }
    int pos = 1;
    while (head != NULL) {
        char line[MAX_ITEM_PRINT_LEN];
        int len = snprintf(line, MAX_ITEM_PRINT_LEN, "%i: %s\n",
                           pos, head->item_name);
        if (len < 0) {
            return EXIT_FAILURE;
        }
        printf("%s", line);
        head = head->next;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // check the list and the item name
    if (*head == NULL || item_name == NULL) {
        return EXIT_FAILURE;
    }
    // check the pos
    if (pos == 0) {
        return EXIT_FAILURE;
    }
    // create a new node
    node *new_node = malloc(sizeof(node));
    new_node->item_name = strdup(item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;
    // if the pos is 1, add the node to the head
    if (pos == 1) {
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    // else, add the node to the tail
    node *tail = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (tail->next == NULL) {
            return EXIT_FAILURE;
        }
        tail = tail->next;
    }
    new_node->next = tail->next;
    tail->next = new_node;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // check the list and the item name
    if (*head == NULL || item_name == NULL) {
        return EXIT_FAILURE;
    }
    // check the pos
    if (pos == 0) {
        return EXIT_FAILURE;
    }
    // if the pos is 1, update the head
    if (pos == 1) {
        (*head)->item_name = strdup(item_name);
        (*head)->price = price;
        (*head)->quantity = quantity;
        return EXIT_SUCCESS;
    }
    // else, update the tail
    node *tail = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (tail->next == NULL) {
            return EXIT_FAILURE;
        }
        tail = tail->next;
    }
    tail->next->item_name = strdup(item_name);
    tail->next->price = price;
    tail->next->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    // check the list
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // check the pos
    if (pos == 0) {
        return EXIT_FAILURE;
    }
    // if the pos is 1, remove the head
    if (pos == 1) {
        node *temp = (*head)->next;
        free((*head)->item_name);
        free(*head);
        *head = temp;
        return EXIT_SUCCESS;
    }
    // else, remove the tail
    node *tail = *head;
    for (int i = 1; i < pos - 1; i++) {
        if (tail->next == NULL) {
            return EXIT_FAILURE;
        }
        tail = tail->next;
    }
    node *temp = tail->next->next;
    free(tail->next->item_name);
    free(tail->next);
    tail->next = temp;
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // check the list
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    // check the pos
    if (pos1 == 0 || pos2 == 0) {
        return EXIT_FAILURE;
    }
    // if the pos is 1, swap the head
    if (pos1 == 1 && pos2 == 1) {
        node *tail = *head;
        for (int i = 1; i < pos2 - 1; i++) {
            if (tail->next == NULL) {
                return EXIT_FAILURE;
            }
            tail = tail->next;
        }
        node *temp = *head;
        *head = tail->next;
        tail->next = temp;
        return EXIT_SUCCESS;
    }
    // else, swap the tail
    node *tail1 = *head;
    for (int i = 1; i < pos1 - 1; i++) {
        if (tail1->next == NULL) {
            return EXIT_FAILURE;
        }
        tail1 = tail1->next;
    }
    node *tail2 = *head;
    for (int i = 1; i < pos2 - 1; i++) {
        if (tail2->next == NULL) {
            return EXIT_FAILURE;
        }
        tail2 = tail2->next;
    }
    node *temp = tail1->next;
    tail1->next = tail2->next;
    tail2->next = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    // check the list
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // check the head
    if (head->next == NULL) {
        if (pos != NULL) {
            *pos = 1;
        }
        return EXIT_SUCCESS;
    }
    // find the position with the highest single price
    node *tail = head;
    float highest_price = head->price;
    (*pos) = 1;
    for (int i = 1; tail != NULL; i++) {
        if (tail->price > highest_price) {
            highest_price = tail->price;
            (*pos) = i + 1;
        }
        tail = tail->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    // check the list
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // check the head
    if (head->next == NULL) {
        *total = head->price * head->quantity;
        return EXIT_SUCCESS;
    }
    // calculate the sum
    node *tail = head;
    float sum = head->price * head->quantity;
    while (tail->next != NULL) {
        sum = sum + tail->next->price * tail->next->quantity;
        tail = tail->next;
    }
    *total = sum;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    // check the list
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // check the filename
    if (filename == NULL) {
        return EXIT_FAILURE;
    }
    // open the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    // write the list to the file
    node *tail = head;
    while (tail!= NULL) {
        fprintf(file, "%s,%f,%d\n", tail->item_name, tail->price, tail->quantity);
        tail = tail->next;
    }
    // close the file
    fclose(file);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}
