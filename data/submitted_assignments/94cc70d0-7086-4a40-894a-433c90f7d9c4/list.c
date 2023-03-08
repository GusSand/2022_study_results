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
//  or EXIT_SUCCESS to indicate whether the operation was 
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
    int res = sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    if(res < 0)
        return EXIT_FAILURE;
    // TODO: Implements this function, 
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
    node* current = head;
    char* current_string = malloc(sizeof(MAX_ITEM_PRINT_LEN));
    int res, i=1;
    while(current != NULL){
        res = list_item_to_string(current,current_string);
        if(res == EXIT_FAILURE)
            return EXIT_FAILURE;
        printf("%d: %s\n", i, current_string);
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // create new element
    node* new_node = (node*) malloc(sizeof(node));
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;

    if(*head == NULL){
        // printf("first element at %p", *head);
        *head = new_node;
        return EXIT_SUCCESS;
    }
    int current_pos = 1;
    node* pointer = *head;
    while(current_pos < pos-1){
        pointer = pointer->next;
        if(pointer == NULL)
            return EXIT_FAILURE;
        
        current_pos++;
    }
    node* before = pointer;
    node* after = pointer->next;

    before->next = new_node;
    new_node->next = after;
    return EXIT_SUCCESS;
}


// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node* current = *head;
    int current_pos = 1;
    while(current_pos < pos){
        current = current->next;
        if(current == NULL)
            return EXIT_FAILURE;
        current_pos++;
    }

    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    node* current = *head;
    int current_pos = 1;
    if(pos == 1){
        free(*head);
        *head = NULL;
        return EXIT_SUCCESS; 
    }
    while(current_pos < pos - 1){
        current = current->next;
        if(current->next == NULL)
            return EXIT_FAILURE;
        current_pos++;
    }
    node* before = current;
    node* to_remove = current->next;
    node* after = to_remove->next;

    before->next = after;
    free(to_remove);
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node* current = *head;
    int current_pos = 1;
    while(current_pos < pos1){
        current = current->next;
        current_pos++;
    }

    char* temp_item_name = current->item_name;
    float temp_price = current->price;
    int temp_quantity = current->quantity;

    current_pos = 1;
    current = *head;
    while(current_pos < pos2){
        current= current->next;
        current_pos++;
    }

    node* node2 = current;

    int res = list_update_item_at_pos(head, node2->item_name, node2->price, node2->quantity, pos1);
    if(res == EXIT_FAILURE)
        return EXIT_FAILURE;
    res = list_update_item_at_pos(head, temp_item_name, temp_price, temp_quantity, pos2);
    if(res == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    node* current = head;
    float max_price = head->price;
    int current_pos = 1;
    *pos = 1;
    while(current != NULL){
        if(current->price > max_price){
            *pos = current_pos;
        }
        current_pos ++;
        current = current->next;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    node* current = head;
    while(current != NULL){
        *total += current->price * current->quantity;
        current = current->next;
    }
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE* fptr = fopen(filename, "a");
    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    node* current = head;

    while(current != NULL){
        fprintf(fptr, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }
    
    fclose(fptr);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    FILE* fptr = fopen(filename, "r");
    node* current = *head;
    int pos = 1;

    char* item_name = malloc(MAX_ITEM_PRINT_LEN);
    float *price = malloc(sizeof(float));
    int *quantity = malloc(sizeof(int));

    while(current != NULL && current->next != NULL){
        current = current->next;
        pos++;
        if(current->next == NULL)
            pos++;
    }
    
    int res;
    while(fscanf(fptr, "%s,%f,%d", item_name, price, quantity) != EOF){
        res = list_add_item_at_pos(head, item_name, *price, *quantity, (unsigned int) pos);
        if (res == EXIT_FAILURE)
            return EXIT_FAILURE;
        pos++;
        
    }
    free(item_name);
    free(price);
    free(quantity);
    fclose(fptr);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    node* current = *head;
    node* next;
    int pos1 = 1, pos2= 2;
    while(current != NULL && current->next != NULL){
        node* second_ptr = current->next;
        while(second_ptr != NULL ){
            if(current->item_name == second_ptr->item_name){
                int total_quantity = current->quantity + second_ptr->quantity;
                
            }
            pos2++;
        }
        pos1++;
    }
    return EXIT_FAILURE;
}

