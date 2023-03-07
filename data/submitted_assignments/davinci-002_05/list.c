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
    if (head == NULL) {
        return EXIT_FAILURE;
    }
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
    int count = 1;
    char str[MAX_ITEM_PRINT_LEN];
    while (head != NULL) {
        list_item_to_string(head, str);
        printf("%d: %s\n", count, str);
        count++;
        head = head->next;
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
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL) {
        return EXIT_FAILURE;
    }
    new_node->item_name = (char *)malloc(sizeof(char) * (strlen(item_name) + 1));
    if (new_node->item_name == NULL) {
        return EXIT_FAILURE;
    }
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;
    if (pos == 1) {
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    node *prev = *head;
    node *curr = *head;
    while (curr != NULL && pos > 1) {
        prev = curr;
        curr = curr->next;
        pos--;
    }
    new_node->next = curr;
    prev->next = new_node;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (pos == 1) {
        node *curr = *head;
        strcpy(curr->item_name, item_name);
        curr->price = price;
        curr->quantity = quantity;
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    while (curr != NULL && pos > 1) {
        curr = curr->next;
        pos--;
    }
    strcpy(curr->item_name, item_name);
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    if (pos == 1) {
        node *curr = *head;
        *head = curr->next;
        free(curr->item_name);
        free(curr);
        return EXIT_SUCCESS;
    }
    node *prev = *head;
    node *curr = *head;
    while (curr != NULL && pos > 1) {
        prev = curr;
        curr = curr->next;
        pos--;
    }
    prev->next = curr->next;
    free(curr->item_name);
    free(curr);
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    if (pos1 == 1 && pos2 == 2) {
        node *curr = *head;
        node *next = curr->next;
        curr->next = next->next;
        next->next = curr;
        *head = next;
        return EXIT_SUCCESS;
    }
    node *prev1 = *head;
    node *curr1 = *head;
    while (curr1 != NULL && pos1 > 1) {
        prev1 = curr1;
        curr1 = curr1->next;
        pos1--;
    }
    node *prev2 = *head;
    node *curr2 = *head;
    while (curr2 != NULL && pos2 > 1) {
        prev2 = curr2;
        curr2 = curr2->next;
        pos2--;
    }
    if (curr1 == NULL || curr2 == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == 1) {
        prev2->next = curr1;
        prev1->next = curr2;
        node *temp = curr1->next;
        curr1->next = curr2->next;
        curr2->next = temp;
        *head = curr2;
        return EXIT_SUCCESS;
    }
    if (pos2 == 1) {
        prev1->next = curr2;
        prev2->next = curr1;
        node *temp = curr2->next;
        curr2->next = curr1->next;
        curr1->next = temp;
        *head = curr1;
        return EXIT_SUCCESS;
    }
    prev1->next = curr2;
    prev2->next = curr1;
    node *temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    *pos = 0;
    float max = 0.0;
    while (head != NULL) {
        float price = head->price * (float)head->quantity;
        if (price > max) {
            max = price;
            *pos = 1;
        } else {
            (*pos)++;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    *total = 0.0;
    while (head != NULL) {
        *total += head->price * (float)head->quantity;
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return EXIT_FAILURE;
    }
    char str[MAX_ITEM_PRINT_LEN];
    while (head != NULL) {
        fprintf(f, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(f);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return EXIT_FAILURE;
    }
    char str[MAX_ITEM_PRINT_LEN];
    while (fgets(str, MAX_ITEM_PRINT_LEN, f) != NULL) {
        char item_name[MAX_ITEM_PRINT_LEN];
        float price;
        int quantity;
        sscanf(str, "%[^,],%f,%d\n", item_name, &price, &quantity);
        list_add_item_at_pos(head, item_name, price, quantity, 0);
    }
    fclose(f);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    node *curr = *head;
    while (curr != NULL) {
        node *prev = curr;
        node *dup = curr->next;
        while (dup != NULL) {
            if (strcmp(curr->item_name, dup->item_name) == 0) {
                curr->quantity += dup->quantity;
                prev->next = dup->next;
                free(dup->item_name);
                free(dup);
                dup = prev->next;
            } else {
                prev = dup;
                dup = dup->next;
            }
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}
