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
    if ((head == NULL) || (str == NULL)){
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
    int i = 1;
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *current = head;
    while (current != NULL) {
        char str[MAX_ITEM_PRINT_LEN];
        if (list_item_to_string(current, str) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }
        printf("%d: %s\n", i, str);
        i++;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    node *newNode = (node*)malloc(sizeof(node));
    newNode->item_name = item_name;
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;
    if ((head == NULL) || (*head == NULL)){
        *head = newNode;
        return EXIT_SUCCESS;
    }
    node *current = *head;
    int i = 1;
    while (i < pos-1 && current->next != NULL){
        current = current->next;
        i++;
    }
    if (i == pos-1){
        newNode->next = current->next;
        current->next = newNode;
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if ((head == NULL) || (*head == NULL)){
        return EXIT_FAILURE;
    }
    node *current = *head;
    int i = 1;
    while (i < pos && current != NULL){
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {    
    if ((head == NULL) || (*head == NULL)) {
        return EXIT_FAILURE;
    }
    int i = 1;
    node *current = *head;
    node *prev = NULL;
    while (i < pos && current != NULL) {
        prev = current;
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if ((head == NULL) || (*head == NULL) || (pos1 == 0) || (pos2 == 0)) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    } else if (pos1 > pos2) {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    int i = 1;
    node *current = *head;
    while (i < pos1 && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    node *item1 = current;
    while (i < pos2 && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    node *item2 = current;
    int temp_quantity = item1->quantity;
    float temp_price = item1->price;
    char *temp_item_name = item1->item_name;
    item1->quantity = item2->quantity;
    item1->price = item2->price;
    item1->item_name = item2->item_name;
    item2->quantity = temp_quantity;
    item2->price = temp_price;
    item2->item_name = temp_item_name;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    if ((head == NULL) || (pos == 0)) {
        return EXIT_FAILURE;
    }
    float max_price = 0.0;
    int max_pos = 0;
    int i = 1;
    node *current = head;
    while (current != NULL) {
        if (current->price > max_price) {
            max_price = current->price;
            max_pos = i;
        }
        current = current->next;
        i++;
    }
    *pos = max_pos;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    float total_cost = 0.0;
    node *current = head;
    while (current != NULL) {
        total_cost += current->quantity * current->price;
        current = current->next;
    }
    *total = total_cost;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    if ((head == NULL) || (filename == NULL)) {
        return EXIT_FAILURE;
    }
    FILE *ptr = fopen(filename, "w");
    node *current = head;
    while (current != NULL) {
        char str[MAX_ITEM_PRINT_LEN] = "";
        sprintf(str, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        fwrite(str, strlen(str), 1, ptr);
        current = current->next;
    }
    fclose(ptr);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    if (filename == NULL) {
        return EXIT_FAILURE;
    }
    node *current = *head;
    if ((current != NULL) && (current->next != NULL)) {
        current = current->next;
    }
    FILE *ptr = fopen(filename, "r");
    char line[MAX_ITEM_PRINT_LEN];
    while (fgets(line, sizeof(line), ptr)) {
        line[strcspn(line, "\n")] = 0;
        node *newNode = (node*)malloc(sizeof(node));
        newNode->item_name = strdup(strtok(line, ","));
        newNode->price = atof(strtok(NULL, ","));
        newNode->quantity = atoi(strtok(NULL, ","));
        newNode->next = NULL;
        if (*head == NULL) {
            *head = newNode;
            current = *head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }
    fclose(ptr);
    return EXIT_SUCCESS;
}


// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if ((head == NULL) || (*head == NULL)) {
        return EXIT_FAILURE;
    }
    node *current = *head;
    node *possible_dup = NULL;
    node *prev_possible_dup = NULL;
    while (current != NULL) {
        possible_dup = current->next;
        prev_possible_dup = current;
        while (possible_dup != NULL) {
            if (strcmp(current->item_name, possible_dup->item_name) == 0) {
                // doesn't say to check if the prices are same or not
                current->quantity += possible_dup->quantity;
                prev_possible_dup->next = possible_dup->next;
            }
            prev_possible_dup = possible_dup;
            possible_dup = possible_dup->next;
        }
        current = current->next;
    }
    return EXIT_SUCCESS;
}

