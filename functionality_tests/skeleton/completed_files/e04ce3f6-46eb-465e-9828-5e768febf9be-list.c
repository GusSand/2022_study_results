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
    // TODO: Implement this function
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
    node* curr = head;
    char* str;
    int i = 1;
    while (curr != NULL) {
        str = malloc(MAX_ITEM_PRINT_LEN);
        list_item_to_string(curr, str);
        printf("%d: %s\n", i, str);
        free(str);
        i++;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

// Destroy the list. This should be a very simple operation, 
// so no error checks are required.
int list_destroy(node **head) {
    node* curr = *head;
    while (*head != NULL) {
        curr = *head;
        *head = (*head)->next;
        free(curr);
    }
    return EXIT_SUCCESS;
}

node* get_item_at_pos(node** head, int pos) {
    node* curr = *head;
    int i = 1;
    while (curr != NULL) {
        if (i == pos) {
            return curr;
        }
        curr = curr->next;
        i++;
    }
    return NULL;
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
    node *item = malloc(sizeof(node));
    char* temp = malloc(sizeof(item_name));
    strcpy(temp, item_name);
    item->item_name = temp;
    item->price = price;
    item->quantity = quantity;

    node *curr = *head;

    if (pos == 1) {
        item->next = *head;
        *head = item;
        return EXIT_SUCCESS;
    }

    for (unsigned int i = 1; i < pos-1; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }

    item->next = curr->next;
    curr->next = item;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (pos < 1 || head == NULL) {
        return EXIT_FAILURE;
    }

    node *curr = *head;
    int i = 1;
    while (curr && i < pos - 1) {
        curr = curr->next;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }

    node *item = malloc(sizeof(node));
    char* temp = malloc(sizeof(item_name));
    strcpy(temp, item_name);
    curr->item_name = temp;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    if(pos < 1 || head == NULL) {
        return EXIT_FAILURE;
    }

    node *curr = *head;
    node *prev = NULL;
    int i = 1;
    while (curr->next && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (i < pos) {
        return EXIT_FAILURE;
    }

    if (curr->next == NULL) {
        if (prev == NULL) {
            *head = NULL;
        } else {
            prev->next = NULL;
        }
        free(curr);
    } else {
        prev->next = curr->next;
        free(curr);
    }
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node* item1 = get_item_at_pos(head, pos1);
    node* item2 = get_item_at_pos(head, pos2);
    if (item1 == NULL || item2 == NULL) {
        return EXIT_FAILURE;
    }

    char* temp_item_name = item1->item_name;
    item1->item_name = item2->item_name;
    item2->item_name = temp_item_name;

    float temp_price = item1->price;
    item1->price = item2->price;
    item2->price = temp_price;

    int temp_quantity = item1->quantity;
    item1->quantity = item2->quantity;
    item2->quantity = temp_quantity;

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = head;
    int i = 1;
    float highest = 0.0;
    while (curr != NULL) {
        if (curr->price > highest) {
            *pos = i;
            highest = curr->price;
        }
        curr = curr->next;
        i++;
    }

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    node* curr = head;
    *total = 0;

    while (curr) {
        *total += (curr->quantity * curr->price);
        curr = curr->next;
    }

    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE* fp;
    fp = fopen(filename, "w+");

    if (!fp) {
        return EXIT_FAILURE;
    }

    node* curr = head;

    while (curr) {
        fprintf(fp, "%s,%.2f,%d\n",
            curr->item_name, curr->price, curr->quantity);
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
int list_load(node **head, char *filename)
{
    FILE* fd;
    fd = fopen(filename, "r");

    if (!fd) {
        return EXIT_FAILURE;
    }

    char* curr_line = malloc(2048*sizeof(char));
    unsigned int i = 1;
    unsigned int n = 0;
    char* delim = ",";
    int c;
    
    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            curr_line[n] = '\0';
            n = 0;

            char* arr[3];
            arr[0] = strtok(curr_line, delim);
            arr[1] = strtok(NULL, delim);
            arr[2] = strtok(NULL, delim);

            list_add_item_at_pos(head, arr[0],
                atof(arr[1]), atoi(arr[2]), i++);
            curr_line[0] = '\0';
        } else {
            curr_line[n++] = (char)c;
        }
    }

    free(curr_line);
    fclose(fd);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    int capacity = 128;
    char** item_names = malloc(capacity*sizeof(char*));
    
    node *curr = *head;
    int pos = 1;

    while (curr) {
        if (pos >= capacity) {
            capacity *= 2;
            item_names = realloc(item_names, capacity*sizeof(char*));
        }

        int found = 0;

        for (unsigned int i = 0; i < pos - 1 && !found; ++i) {
            if (strcmp(curr->item_name, item_names[i]) == 0) {
                node* to_update = get_item_at_pos(head, i+1);
                list_update_item_at_pos(head,
                    to_update->item_name,
                    to_update->price,
                    to_update->quantity + curr->quantity,
                    i+1);
                
                curr = curr->next;
                list_remove_item_at_pos(head, pos);
                found = 1;
            }
        }

        if (!found) {
            item_names[pos-1] = curr->item_name;
            pos++;
            curr = curr->next;
        }
    }

    return EXIT_SUCCESS;
}

