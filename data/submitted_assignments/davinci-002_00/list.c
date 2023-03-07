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
    int ret = snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea",
                        head->quantity, head->item_name, head->price);
    if (ret >= MAX_ITEM_PRINT_LEN) {
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
    while (head) {
        char buf[MAX_ITEM_PRINT_LEN];
        list_item_to_string(head, buf);
        printf("%d: %s\n", pos, buf);
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
    if (*head == NULL || pos == 0) {
        return EXIT_FAILURE;
    }
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item_name = malloc(strlen(item_name) + 1);
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;
    int cur_pos = 1;
    node *cur = *head;
    while (cur->next && cur_pos < pos-1) {
        cur = cur->next;
        cur_pos++;
    }
    if (cur_pos == pos-1) {
        new_node->next = cur->next;
        cur->next = new_node;
    } else {
        free(new_node);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (*head == NULL || pos == 0) {
        return EXIT_FAILURE;
    }
    int cur_pos = 1;
    node *cur = *head;
    while (cur->next && cur_pos < pos) {
        cur = cur->next;
        cur_pos++;
    }
    if (cur_pos == pos) {
        free(cur->item_name);
        cur->item_name = malloc(strlen(item_name) + 1);
        strcpy(cur->item_name, item_name);
        cur->price = price;
        cur->quantity = quantity;
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    if (*head == NULL || pos == 0) {
        return EXIT_FAILURE;
    }
    int cur_pos = 1;
    node *cur = *head;
    while (cur->next && cur_pos < pos-1) {
        cur = cur->next;
        cur_pos++;
    }
    if (cur_pos == pos-1) {
        node *temp = cur->next;
        cur->next = cur->next->next;
        free(temp->item_name);
        free(temp);
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (*head == NULL || pos1 == 0 || pos2 == 0) {
        return EXIT_FAILURE;
    }
    int cur_pos = 1;
    node *cur = *head;
    while (cur->next && cur_pos < pos1-1) {
        cur = cur->next;
        cur_pos++;
    }
    if (cur_pos == pos1-1) {
        node *temp = cur->next;
        cur->next = cur->next->next;
        cur = cur->next;
        cur_pos++;
        while (cur->next && cur_pos < pos2-1) {
            cur = cur->next;
            cur_pos++;
        }
        if (cur_pos == pos2-1) {
            node *temp2 = cur->next;
            cur->next = temp;
            temp->next = temp2->next;
            free(temp2->item_name);
            free(temp2);
        } else {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        *pos = 0;
        return EXIT_FAILURE;
    }
    *pos = 1;
    int cur_pos = 1;
    float max_price = head->price;
    node *cur = head->next;
    while (cur) {
        if (cur->price > max_price) {
            *pos = cur_pos+1;
            max_price = cur->price;
        }
        cur = cur->next;
        cur_pos++;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    *total = 0;
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    while (head) {
        *total += head->price * head->quantity;
        head = head->next;
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
        return EXIT_FAILURE;
    }
    while (head) {
        fprintf(fp, "%s,%f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
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
        return EXIT_FAILURE;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (read <= 3) {
            continue;
        }
        if (line[read-1] == '\n') {
            line[read-1] = '\0';
        }
        char *token = strtok(line, ",");
        char *item_name = malloc(strlen(token) + 1);
        strcpy(item_name, token);
        token = strtok(NULL, ",");
        float price = atof(token);
        token = strtok(NULL, ",");
        int quantity = atoi(token);
        if (*head == NULL) {
            *head = (node *)malloc(sizeof(node));
            (*head)->item_name = item_name;
            (*head)->price = price;
            (*head)->quantity = quantity;
            (*head)->next = NULL;
        } else {
            node *cur = *head;
            while (cur->next) {
                cur = cur->next;
            }
            cur->next = (node *)malloc(sizeof(node));
            cur->next->item_name = item_name;
            cur->next->price = price;
            cur->next->quantity = quantity;
            cur->next->next = NULL;
        }
    }
    fclose(fp);
    if (line) {
        free(line);
    }
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    node *cur = *head;
    node *prev = cur;
    while (cur->next) {
        if (strcmp(cur->item_name, cur->next->item_name) == 0) {
            cur->quantity += cur->next->quantity;
            node *temp = cur->next;
            cur->next = cur->next->next;
            free(temp->item_name);
            free(temp);
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return EXIT_SUCCESS;
}
