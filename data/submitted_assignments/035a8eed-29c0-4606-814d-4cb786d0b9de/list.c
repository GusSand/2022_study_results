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
    if (head != NULL) {
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
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
    int counter = 1;
    while (head != NULL) {
        printf("%d: %d * %s @ $%.2f ea\n", counter, head->quantity, head->item_name, head->price);
        head = head->next;
        counter++;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    node* n = *head;
    node* new_node = NULL;
    int counter = 1;

    if (pos == 1) {
        new_node = malloc(sizeof(struct _node));
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = n;
        *head = new_node;
        return EXIT_SUCCESS;
    }

    while (n != NULL) {
        if (counter == pos-1) {
            new_node = malloc(sizeof(struct _node));
            new_node->item_name = item_name;
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = n->next;
            n->next = new_node;
            return EXIT_SUCCESS;
        }
        n = n->next;
        counter++;
    }
    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    unsigned int counter = 1;
    node* n = *head;
    while(n != NULL) {
        if (counter == pos) {
            n->item_name = item_name;
            n->price = price;
            n->quantity = quantity;
            return EXIT_SUCCESS;
        }
        n = n->next;
    }
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    node* n = *head;
    int counter = 1;

    if (pos == 1) {
        *head = n->next;
        free(n);
        return EXIT_SUCCESS;
    }

    while (n != NULL) {
        if (counter == pos-1) {
            node* next_node = n->next;
            n->next = next_node->next;
            free(next_node);
            return EXIT_SUCCESS;
        }
        n = n->next;
        counter++;
    }

    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node* n = *head;
    node* pos1_parent = NULL;
    node* pos2_parent = NULL;

    if (pos1 < 1 || pos2 < 1) return EXIT_FAILURE;
    if (pos1 == pos2) return EXIT_SUCCESS;

    pos1 = (pos1 < pos2) ? pos1 : pos2;
    pos2 = (pos2 < pos1) ? pos1 : pos2;

    int counter = 1;
    while(n != NULL) {
        if (counter == pos1-1) {
            pos1_parent = n;
        }
        if (counter == pos2-1) {
            pos2_parent = n;
        }
        n = n->next;
        counter++;
    }

    if (pos2_parent == NULL) return EXIT_FAILURE;

    node* node1 = NULL;
    node* node2 = pos2_parent->next;

    if (pos1_parent == NULL) {
        node1 = *head;
        *head = node2;
    }
    else {
        node1 = pos1_parent->next;
        pos1_parent->next = node2;
    }

    pos2_parent->next = node1;

    node* temp = node2->next;
    node2->next = node1->next;
    node1->next = temp;

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    int counter = 0;
    int max = -1;

    while (head != NULL) {
        counter++;

        if (head->price > max) max = head->price;
        head = head->next;
    }

    *pos = counter;

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    float sum = 0;

    while (head != NULL) {
        sum += head->price * head->quantity;
        head = head->next;
    }

    *total = sum;

    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE* fileptr = NULL;

    fileptr = fopen(filename, "w");

    if (fileptr == NULL ) {
        return EXIT_FAILURE;
    }

    while (head != NULL) {
        fprintf(fileptr, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }

    fclose(fileptr);

    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    list_init(head);

    FILE* fileptr = NULL;
    char* line;
    size_t size = MAX_ITEM_PRINT_LEN;

    if((fileptr = fopen(filename, "r")) == NULL) {
        return EXIT_FAILURE;
    }

    char* item_name;
    float price;
    int quantity;
    int pos = 1;

    while (getline(&line, &size, fileptr) != -1) {
        item_name = strtok(line, ",");
        char* str = (char*)malloc(strlen(item_name));
        strcpy(str,item_name);
        price = atof(strtok(NULL, ","));
        quantity = atoi(strtok(NULL, ","));
        list_add_item_at_pos(head, str, price, quantity, pos);
        pos++;
    }

    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    node* n = *head;
    int pos_n = 1;

    while (n != NULL) {
        node* m = n->next;
        int pos_m = pos_n+1;
        while (m != NULL) {
            if (strcmp(n->item_name, m->item_name) == 0) {
                n->quantity += m->quantity;
                list_remove_item_at_pos(head, pos_m);
            }
            m = m->next;
            pos_m++;
        }
        n = n->next;
        pos_n++;
    }

    return EXIT_SUCCESS;
}

