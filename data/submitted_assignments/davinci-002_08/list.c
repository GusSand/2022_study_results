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
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    if (str == NULL || head == NULL) {
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
    node *curr = head;
    int i = 1;
    while (curr != NULL) {
        char *str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
        list_item_to_string(curr, str);
        printf("%d: %s\n", i, str);
        curr = curr->next;
        i++;
        free(str);
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
    node *curr = *head;
    node *prev = NULL;
    int i = 1;

    if (head == NULL || item_name == NULL) {
        return EXIT_FAILURE;
    }

    if (pos == 0) {
        node *new = malloc(sizeof(node));
        new->item_name = malloc(strlen(item_name) * sizeof(char) + 1);
        memset(new->item_name, 0, strlen(item_name) * sizeof(char) + 1);
        strcpy(new->item_name, item_name);
        new->price = price;
        new->quantity = quantity;
        new->next = *head;
        *head = new;
        return EXIT_SUCCESS;
    }

    while (curr != NULL) {
        if (i == pos) {
            node *new = malloc(sizeof(node));
            new->item_name = malloc(strlen(item_name) * sizeof(char) + 1);
            memset(new->item_name, 0, strlen(item_name) * sizeof(char) + 1);
            strcpy(new->item_name, item_name);
            new->price = price;
            new->quantity = quantity;
            new->next = curr;
            if (prev != NULL) {
                prev->next = new;
            }
            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node *curr = *head;
    int i = 1;

    if (head == NULL || item_name == NULL) {
        return EXIT_FAILURE;
    }

    while (curr != NULL) {
        if (i == pos) {
            curr->item_name = realloc(curr->item_name, strlen(item_name) * sizeof(char) + 1);
            memset(curr->item_name, 0, strlen(item_name) * sizeof(char) + 1);
            strcpy(curr->item_name, item_name);
            curr->price = price;
            curr->quantity = quantity;
            return EXIT_SUCCESS;
        }
        curr = curr->next;
        i++;
    }
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    node *curr = *head;
    node *prev = NULL;
    int i = 1;

    if (head == NULL) {
        return EXIT_FAILURE;
    }

    if (pos == 0) {
        *head = curr->next;
        free(curr->item_name);
        free(curr);
        return EXIT_SUCCESS;
    }

    while (curr != NULL) {
        if (i == pos) {
            prev->next = curr->next;
            free(curr->item_name);
            free(curr);
            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node *curr1 = *head;
    node *prev1 = NULL;
    node *curr2 = *head;
    node *prev2 = NULL;
    int i = 1;

    if (head == NULL) {
        return EXIT_FAILURE;
    }

    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }

    while (curr1 != NULL) {
        if (i == pos1) {
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
        i++;
    }
    i = 1;
    while (curr2 != NULL) {
        if (i == pos2) {
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
        i++;
    }

    if (pos1 == 0) {
        curr2->next = curr1;
        prev1->next = curr2;
        *head = curr2;
        return EXIT_SUCCESS;
    }
    if (pos2 == 0) {
        curr1->next = curr2;
        prev2->next = curr1;
        *head = curr1;
        return EXIT_SUCCESS;
    }

    prev1->next = curr2;
    node *temp = curr2->next;
    curr2->next = curr1->next;
    prev2->next = curr1;
    curr1->next = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    int max = 0;
    int curr_pos = 0;
    int i = 1;
    node *curr = head;
    while (curr != NULL) {
        if (curr->price > max) {
            max = curr->price;
            curr_pos = i;
        }
        curr = curr->next;
        i++;
    }
    *pos = curr_pos;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    float sum = 0;
    node *curr = head;
    while (curr != NULL) {
        sum += curr->price * curr->quantity;
        curr = curr->next;
    }
    *total = sum;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    node *curr = head;
    char *str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
    while (curr != NULL) {
        sprintf(str, "%s,%.2f,%d\n", curr->item_name, curr->price, curr->quantity);
        fputs(str, file);
        curr = curr->next;
    }
    free(str);
    fclose(file);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    char *line = malloc(MAX_ITEM_PRINT_LEN * sizeof(char) + 1);
    while (fgets(line, MAX_ITEM_PRINT_LEN, file) != NULL) {
        char *item_name = strtok(line, ",");
        float price = atof(strtok(NULL, ","));
        int quantity = atoi(strtok(NULL, ","));
        list_add_item_at_pos(head, item_name, price, quantity, 0);
    }
    free(line);
    fclose(file);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    node *curr = *head;
    node *prev = NULL;
    while (curr != NULL) {
        node *check = curr->next;
        prev = curr;
        while (check != NULL) {
            if (strcmp(curr->item_name, check->item_name) == 0) {
                curr->quantity += check->quantity;
                prev->next = check->next;
                free(check->item_name);
                free(check);
                check = prev->next;
            } else {
                check = check->next;
                prev = prev->next;
            }
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}
