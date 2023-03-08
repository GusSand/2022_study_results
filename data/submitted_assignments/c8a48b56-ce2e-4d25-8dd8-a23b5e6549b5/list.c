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

    if (head != NULL){
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    }
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
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
    node* cur;
    cur = head;
    int i = 0;
    while (cur != NULL){
        i++;
        printf("%d: %d * %s @ $%.2f ea\n",i,cur->quantity,cur->item_name,cur->price);
        cur = cur->next;
    }
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
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
    node* cur = *head;
    node* prev = NULL;
    for (int i=1; i<pos; i++){
        prev = cur;
        cur = cur->next;
    }
    node* new_node = malloc(sizeof(node));
    if (pos==1){
        
        new_node->next = *head;
        *head = new_node;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->item_name = item_name;
        return EXIT_SUCCESS;
    }
    new_node->next = prev->next;
    prev->next = new_node;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->item_name = item_name;
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    node* cur = *head;
    for (int i=1; i<pos; i++){
        cur = cur->next;
    }
    cur->price = price;
    cur->quantity = quantity;
    cur->item_name = item_name;
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    node *cur = *head;
    node *prev, *temp;
    if (pos==1){
        temp = *head;
        *head = temp->next;
        temp = NULL;
        return EXIT_SUCCESS;
    }
    for (int i=1; i<pos; i++){
        prev = cur;
        cur = cur->next;
    }

    prev->next = cur->next;
    cur = NULL;
    
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    int mind, maxd;
    if (pos1<=pos2){mind = pos1; maxd = pos2;}
    else {mind = pos2; maxd = pos1;}

    node* min = *head;
    node* max = *head;
    node* temp = *head;
    int i=1;

    while (temp != NULL){        
        if(i==mind){
            max = temp;
            for (int j=i; j<maxd; j++){
                max = max->next;}
            temp = min;
            min->next = max->next;
            max->next = temp->next;          
        }
        i++;
        temp = temp->next;
    }
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    int max = -10000;
    int max_ind;
    node* cur;
    cur->next = head;
    int i = 0;
    while (1){       
        if (cur == NULL){
            break;
        }
        if (cur->price >= max){
            max = cur->price;
            max_ind = i;
        }
        i++;
        cur = cur->next;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    node* cur;
    cur = head;
    int cost = 0;

    while (1){
        if (cur == NULL){
            break;
        }
        cost += cur->price * cur->quantity;
        cur = cur->next;
    }
    *total = cost;
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    node* cur;
    cur = head;

    FILE *file;
    file = fopen(filename, "w");
    while(cur != NULL){
        fprintf(file, "%d,%s,%.2f", cur->quantity, cur->item_name, cur->price);
        cur = cur->next;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
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
    node* cur;
    cur = *head;
    while(cur != NULL){
        cur = cur->next;
    }

    FILE *file;
    file = fopen(filename, "w");
    while(cur != NULL){
        fscanf(file, "%d,%s,%f", &cur->quantity, cur->item_name, &cur->price);
        cur = cur->next;
    }
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    node* cur = *head;
    node* prev = cur;
    
    const char* item_list[10000];
    int flag=0;

    int i=0;
    while (1){
        if(cur == NULL){
            break;
        }
        else{
            item_list[i] = cur->item_name;

        }
        for (int j=0; j<i; j++){
            if (cur->item_name == item_list[j]){
                flag=1;
            }
        }
        if(flag){
            //prev unchanged
            cur = cur->next;           
            i++;
        }
        else{
            prev = cur;
            cur = cur->next;
            i++;
        }

    }
    node* fut = cur->next;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

