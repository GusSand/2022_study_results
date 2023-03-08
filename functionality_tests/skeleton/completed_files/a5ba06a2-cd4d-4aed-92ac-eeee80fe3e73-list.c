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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL || str == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    free(str);
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    int i = 0; char* str = malloc(MAX_ITEM_PRINT_LEN);
    node* cur = head;
    while (cur != NULL) {
        list_item_to_string(cur, str);
        printf("%d: %s\n", i, str);
        i++;
        cur = cur->next;
    }
    free(str);
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    node* cur = *head;
    if(pos == 0) {
        *head = malloc(sizeof(node));
        (*head)->quantity = quantity;
        (*head)->price = price;
        (*head)->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
        strcpy((*head)->item_name, item_name);
        (*head)->next = cur;
        return EXIT_SUCCESS;
    }

    if (pos > 0) {
        if (cur == NULL) {
            return EXIT_FAILURE;
        }
        for (unsigned int i = 1; i < pos; i++) {
            if (cur->next == NULL) {
                return EXIT_FAILURE;
            }
            cur = cur->next;
        }
    }
    node* new = malloc(sizeof(node));
    new->quantity = quantity;
    new->price = price;
    new->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
    strcpy(new->item_name, item_name);
    new->next = cur->next;
    cur->next = new;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    node* cur = *head;
    if (pos == 0) {
        cur->quantity = quantity;
        cur->price = price;
        strcpy(cur->item_name, item_name);
        return EXIT_SUCCESS;
    }
    for (unsigned int i = 0; i < pos; i++) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
    }
    cur->quantity = quantity;
    cur->price = price;
    strcpy(cur->item_name, item_name);
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos == 0) {
        *head = (*head)->next;
        return EXIT_SUCCESS;
    }
    node* cur = *head;
    for (unsigned int i = 0; i < pos - 1; i++) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
    }
    if (cur->next != NULL) {
        cur->next = cur->next->next;
    }
    return EXIT_SUCCESS;
}


// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //
    // Hint: There are many ways to do this
    //
    if (head == NULL || *head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    node* prev1 = NULL;
    node* cur1 = *head;
    for (unsigned int i = 0; i < pos1 - 1; i++) {
        if (cur1->next == NULL) {
            return EXIT_FAILURE;
        }
        prev1 = cur1;
        cur1 = cur1->next;
    }
    node* prev2 = NULL;
    node* cur2 = *head;
    for (unsigned int i = 0; i < pos2 - 1; i++) {
        if (cur2->next == NULL) {
            return EXIT_FAILURE;
        }
        prev2 = cur2;
        cur2 = cur2->next;
    }
    node* temp = cur1->next;
    cur1->next = cur2->next;
    cur2->next = temp;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL || pos == NULL) return EXIT_FAILURE;
    node* cur = head;
    int max_price = 0;
    while (cur != NULL) {
        if (cur->price > max_price) max_price = cur->price;
        cur = cur->next;
    }
    pos = &max_price;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) return EXIT_FAILURE;
    node* cur = head;
    float total_cost = 0;
    while (cur != NULL) {
        total_cost += cur->quantity*cur->price;
        cur = cur->next;
    }
    total = &total_cost;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE * file;
    file = fopen(filename, "w");
    node * cur = head;
    if (file == NULL) return EXIT_FAILURE;
    while (cur != NULL) {
        fprintf(file, "%s,%f,%d\n", cur->item_name, cur->price, cur->quantity);
        cur = cur->next;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE * file;
    file = fopen(filename, "r");
    if (file == NULL) return EXIT_FAILURE;
    node * cur = *head;
    if (cur == NULL) return EXIT_FAILURE;
    while (cur->next != NULL) cur = cur->next;
    char * new_name; int new_price; int new_quant;
    while (fscanf(file, "%s,%d,%d\n", new_name, &new_price, &new_quant) > 0) {
        node * new = malloc(sizeof(node));
        new->item_name = new_name;
        new->price = new_price;
        new->quantity = new_quant;
        cur->next = new;
        new->next = NULL;
        cur = cur->next;
        if (cur == NULL) return EXIT_FAILURE;
    }
    if (fscanf(file, "%s,%d,%d\n", new_name, &new_price, &new_quant) < 0) return EXIT_FAILURE;
    fclose(file);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // two iter nodes. one to go through and another to find duplicates for each node. 
    // when dup found, remove

    node * main = *head;
    node * findDup = *head;
    int count = 0;
    int dupCount;

    if (main == NULL || findDup == NULL) return EXIT_FAILURE;

    while (main->next != NULL) {
        findDup = *head;
        dupCount = 0;
        while (findDup->item_name != main->next->item_name) {
            findDup = findDup->next;
            dupCount ++;
        }
        if (dupCount <= count) { // found duplicate
            findDup->quantity += main->next->quantity;
            main->next = main->next->next;
        } // else did not find duplicate
        main = main->next;
        count++;
    }

    return EXIT_SUCCESS;
}

