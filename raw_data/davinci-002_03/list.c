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
    int i = 1; 
    while (head != NULL) {
        char line[MAX_ITEM_PRINT_LEN];
        list_item_to_string(head, line);
        printf("%d: %s\n", i, line);
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
    node *new_node = (node *) malloc(sizeof(node));
    new_node->item_name = strdup(item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return EXIT_SUCCESS;
    }

    if (pos == 1) {
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }

    int i = 1;
    node *prev = NULL;
    node *current = *head;
    while (current != NULL) {
        if (i == pos) {
            prev->next = new_node;
            new_node->next = current;
            return EXIT_SUCCESS;
        }
        i++;
        prev = current;
        current = current->next;
    }
    if (i == pos) {
        prev->next = new_node;
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    int i = 1;
    node *current = *head;
    while (current != NULL) {
        if (i == pos) {
            free(current->item_name);
            current->item_name = strdup(item_name);
            current->price = price;
            current->quantity = quantity;
            return EXIT_SUCCESS;
        }
        i++;
        current = current->next;
    }
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    int i = 1;
    node *prev = NULL;
    node *current = *head;
    while (current != NULL) {
        if (i == pos) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->item_name);
            free(current);
            return EXIT_SUCCESS;
        }
        i++;
        prev = current;
        current = current->next;
    }
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }

    int i = 1;
    node *prev1 = NULL;
    node *prev2 = NULL;
    node *current1 = *head;
    while (current1 != NULL) {
        if (i == pos1) {
            break;
        }
        i++;
        prev1 = current1;
        current1 = current1->next;
    }

    if (current1 == NULL) {
        return EXIT_FAILURE;
    }

    i = 1;
    node *current2 = *head;
    while (current2 != NULL) {
        if (i == pos2) {
            break;
        }
        i++;
        prev2 = current2;
        current2 = current2->next;
    }

    if (current2 == NULL) {
        return EXIT_FAILURE;
    }

    if (prev1 == NULL) {
        *head = current2;
    } else {
        prev1->next = current2;
    }
    if (prev2 == NULL) {
        *head = current1;
    } else {
        prev2->next = current1;
    }
    node *temp = current1->next;
    current1->next = current2->next;
    current2->next = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    int i = 1;
    int max_price_pos = 1;
    node *current = head;
    while (current != NULL) {
        if (current->price >= head->price) {
            max_price_pos = i;
        }
        i++;
        current = current->next;
    }
    *pos = max_price_pos;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    float sum = 0;
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
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    node *current = head;
    while (current != NULL) {
        fprintf(file, "%s,%f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    char line[MAX_ITEM_PRINT_LEN];
    while (fgets(line, MAX_ITEM_PRINT_LEN, file) != NULL) {
        char *item_name = strdup(strtok(line, ","));
        float price = strtof(strtok(NULL, ","), NULL);
        int quantity = strtol(strtok(NULL, ","), NULL, 10);
        list_add_item_at_pos(head, item_name, price, quantity, -1);
    }
    fclose(file);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    int i = 1;
    node *current = *head;
    while (current != NULL) {
        int j = i + 1;
        node *current2 = current->next;
        while (current2 != NULL) {
            if (strcmp(current->item_name, current2->item_name) == 0) {
                current->quantity += current2->quantity;
                list_remove_item_at_pos(head, j);
            } else {
                j++;
            }
            current2 = current2->next;
        }
        i++;
        current = current->next;
    }
    return EXIT_SUCCESS;
}
