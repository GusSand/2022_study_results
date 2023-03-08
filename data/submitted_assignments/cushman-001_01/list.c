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
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Error: malloc failed\n");
        return EXIT_FAILURE;
    }
    new_node->item_name = NULL;
    new_node->price = 0;
    new_node->quantity = 0;
    new_node->next = *head;
    *head = new_node;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    if (head == NULL || str == NULL) {
        printf("Error: list_item_to_string\n");
        return EXIT_FAILURE;
    }
    char buffer[MAX_ITEM_PRINT_LEN];
    snprintf(buffer, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea",
             head->quantity, head->item_name, head->price);
    strcpy(str, buffer);
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
        printf("Error: list_print\n");
        return EXIT_FAILURE;
    }
    int i = 0;
    while (head != NULL) {
        char buffer[MAX_ITEM_PRINT_LEN];
        snprintf(buffer, MAX_ITEM_PRINT_LEN, "%d: %s\n", i, head->item_name);
        printf("%s", buffer);
        i++;
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
    if (head == NULL || item_name == NULL) {
        printf("Error: list_add_item_at_pos\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    node *prev = NULL;
    while (curr != NULL) {
        if (pos == 0) {
            node *new_node = malloc(sizeof(node));
            new_node->item_name = item_name;
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = curr;
            *head = new_node;
            return EXIT_SUCCESS;
        }
        pos--;
        prev = curr;
        curr = curr->next;
    }
    if (prev == NULL) {
        printf("Error: list_add_item_at_pos\n");
        return EXIT_FAILURE;
    }
    node *new_node = malloc(sizeof(node));
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    prev->next = new_node;
    new_node->next = curr;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (head == NULL || item_name == NULL) {
        printf("Error: list_update_item_at_pos\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    while (curr != NULL) {
        if (pos == 0) {
            curr->item_name = item_name;
            curr->price = price;
            curr->quantity = quantity;
            return EXIT_SUCCESS;
        }
        pos--;
        curr = curr->next;
    }
    printf("Error: list_update_item_at_pos\n");
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    if (head == NULL) {
        printf("Error: list_remove_item_at_pos\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    node *prev = NULL;
    while (curr!= NULL) {
        if (pos == 0) {
            if (prev == NULL) {
                *head = curr->next;
                free(curr);
                return EXIT_SUCCESS;
            }
            prev->next = curr->next;
            free(curr);
            return EXIT_SUCCESS;
        }
        pos--;
        prev = curr;
        curr = curr->next;
    }
    printf("Error: list_remove_item_at_pos\n");
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (head == NULL) {
        printf("Error: list_swap_item_positions\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    node *prev1 = NULL;
    node *prev2 = NULL;
    while (curr!= NULL) {
        if (pos1 == 0) {
            prev1 = NULL;
        }
        if (pos2 == 0) {
            prev2 = NULL;
        }
        if (pos1 == 0 && pos2 == 0) {
            node *tmp = curr->next;
            curr->next = tmp->next;
            tmp->next = curr;
            if (prev1 == NULL) {
                *head = tmp;
            } else {
                prev1->next = tmp;
            }
            if (prev2 == NULL) {
                *head = curr;
            } else {
                prev2->next = curr;
            }
            return EXIT_SUCCESS;
        }
        pos1--;
        pos2--;
        prev1 = curr;
        curr = curr->next;
    }
    printf("Error: list_swap_item_positions\n");
    return EXIT_FAILURE;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        printf("Error: list_find_highest_price_item_position\n");
        return EXIT_FAILURE;
    }
    node *curr = head;
    *pos = 0;
    float max = 0.0;
    while (curr!= NULL) {
        if (curr->price > max) {
            max = curr->price;
            *pos = *pos + 1;
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    if (head == NULL) {
        printf("Error: list_cost_sum\n");
        return EXIT_FAILURE;
    }
    *total = 0.0;
    node *curr = head;
    while (curr!= NULL) {
        *total = *total + curr->price * curr->quantity;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: list_save\n");
        return EXIT_FAILURE;
    }
    node *curr = head;
    while (curr!= NULL) {
        fprintf(fp, "%s,%f,%d\n", curr->item_name, curr->price, curr->quantity);
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
int list_load(node **head, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: list_load\n");
        return EXIT_FAILURE;
    }
    char line[200];
    char *token;
    while (fgets(line, 200, fp) != NULL) {
        int len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        token = strtok(line, ",");
        char *item_name = token;
        token = strtok(NULL, ",");
        float price = atof(token);
        token = strtok(NULL, ",");
        int quantity = atoi(token);
        list_add_item_at_pos(head, item_name, price, quantity, 0);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if (head == NULL) {
        printf("Error: list_deduplicate\n");
        return EXIT_FAILURE;
    }
    node *curr = *head;
    node *prev = NULL;
    while (curr!= NULL) {
        node *tmp = curr->next;
        while (tmp!= NULL) {
            if (strcmp(curr->item_name, tmp->item_name) == 0) {
                curr->quantity = curr->quantity + tmp->quantity;
                if (prev == NULL) {
                    *head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                free(tmp);
                tmp = curr->next;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}
