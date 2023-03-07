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
    node *current = head;
    int i=0, j=0;
    char *p = str;
    while (current!=NULL) {
        int len=0;
        float f = current->price;
        char *item_name = current->item_name;
        len = sprintf(p, "%d * %s @ $%.2f ea", current->quantity, item_name, f);
        p += len;
        i++;
        current = current->next;
        j++;
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
    node *current = head;
    int i=0;
    while (current != NULL) {
        printf("%d: %d * %s @ $%.2f ea\n", i, current->quantity, current->item_name, current->price);
        current = current->next;
        i++;
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
    node *current = *head;
    node *new_node = malloc(sizeof(node));
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;
    int i=0;
    if (pos==0) {
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    while (current != NULL && i<pos) {
        if (i+1==pos) {
            new_node->next = current->next;
            current->next = new_node;
            return EXIT_SUCCESS;
        }
        current = current->next;
        i++;
    }
    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node *current = *head;
    int i=0;
    while (current != NULL && i<pos) {
        if (i+1==pos) {
            current->item_name = item_name;
            current->price = price;
            current->quantity = quantity;
            return EXIT_SUCCESS;
        }
        current = current->next;
        i++;
    }
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    node *current = *head;
    node *prev = NULL;
    int i=0;
    while (current != NULL) {
        if (i+1==pos) {
            if (prev==NULL) {
                *head = current->next;
                free(current);
                return EXIT_SUCCESS;
            }
            prev->next = current->next;
            free(current);
            return EXIT_SUCCESS;
        }
        prev = current;
        current = current->next;
        i++;
    }
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node *current = *head;
    node *prev = NULL;
    int i=0;
    while (current != NULL) {
        if (i+1==pos1) {
            if (prev==NULL) {
                *head = current->next;
                current->next = *head;
                *head = current;
                return EXIT_SUCCESS;
            }
            prev->next = current->next;
            current->next = *head;
            *head = current;
            return EXIT_SUCCESS;
        }
        if (i+1==pos2) {
            if (prev==NULL) {
                *head = current->next;
                current->next = *head;
                *head = current;
                return EXIT_SUCCESS;
            }
            prev->next = current->next;
            current->next = *head;
            *head = current;
            return EXIT_SUCCESS;
        }
        prev = current;
        current = current->next;
        i++;
    }
    return EXIT_FAILURE;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    node *current = head;
    int i=0, j=0;
    float max_price=0.0;
    while (current != NULL) {
        float f = current->price;
        if (f>=max_price) {
            max_price = f;
            j=i;
        }
        current = current->next;
        i++;
    }
    *pos = j;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    node *current = head;
    float f = 0.0;
    while (current != NULL) {
        f += current->quantity*current->price;
        current = current->next;
    }
    *total = f;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    FILE *fp = fopen(filename,"w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    node *current = head;
    while (current != NULL) {
        fprintf(fp, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
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
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    char line[MAX_ITEM_PRINT_LEN+1];
    while (fgets(line, MAX_ITEM_PRINT_LEN, fp)) {
        int i=0;
        int pos1 = 0, pos2 = 0;
        char *item_name = NULL;
        float price = 0.0;
        int quantity = 0;
        while (line[i]!=',' && line[i]!=0) {
            i++;
        }
        if (line[i]==0) {
            break;
        }
        item_name = line;
        i++;
        while (line[i]!=',' && line[i]!=0) {
            i++;
        }
        if (line[i]==0) {
            break;
        }
        pos1 = i+1;
        float f = atof(&line[i+1]);
        i=0;
        while (line[i]!=0) {
            i++;
        }
        if (line[i]==0) {
            break;
        }
        pos2 = i;
        quantity = atoi(&line[pos1]);
        price = f;
        list_add_item_at_pos(head, item_name, price, quantity, pos2);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    node *current = *head;
    node *prev = NULL;
    while (current != NULL) {
        if (prev!=NULL && strcmp(current->item_name, prev->item_name)==0) {
            prev->quantity += current->quantity;
            current = current->next;
            list_remove_item_at_pos(head, prev->quantity);
            //list_print(*head);
        }
        else {
            prev = current;
            current = current->next;
        }
    }
    return EXIT_SUCCESS;
}
