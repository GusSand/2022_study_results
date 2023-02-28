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

    // Allocate String
    if (head == NULL) return EXIT_FAILURE;

    // Else print out node 
    else{
        char * temp = malloc(MAX_ITEM_PRINT_LEN);
        
        // Store name into string 
        char name[100] = "";
        strcpy(name, head->item_name);

        // Store quantity into string 
        char quantity[10] = "";
        sprintf(quantity, "%d", head->quantity);

        // Store price into string 
        float price = head->price;
        char price_arr[MAX_ITEM_PRINT_LEN]; 
        gcvt(price, sizeof(price), price_arr);

        // Print out string with quantity, name, price and quantity 
        sprintf(temp, "%d %s %s %s", head->quantity, name, price_arr, "ea");   
        strcpy(str, temp);

        free(temp);

        //Changing int to String 
        char quant[MAX_ITEM_PRINT_LEN]; 
        int quantity = head->quantity;
        itoa(quantity, quant, sizeof(quantity)); 

        // Format the string
        sprintf(temp, "%d * %s @ $%.2f ea", quantity, item_name, price);

        // Copy the
    }
    return EXIT_FAILURE;
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
    node* curr_node = head; 
    int counter = 1; 
    while(curr_node != NULL) {
        printf("%d: %d * %s @ $%.2f ea\n", counter, curr_node->quantity, curr_node->item_name, curr_node->price);
        curr_node = curr_node->next;
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int position = 0; 
    node *curr_node = *head;
    for (int i = 0; i < pos; i++){
        if (position != pos){
            position++; 
            curr_node = curr_node->next; 
        }
        else{
            node *new_node = malloc(sizeof(node)); 
            // New node contents 
            new_node->item_name = item_name;
            new_node->price = price;
            new_node->quantity = quantity;
            // new_node->pos = pos; 
            curr_node->next = new_node; // Connect the previous node to the new node
        }
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    unsigned curr_pos = 0; // Initialize the current position to 0 
    node* curr_node = head; 
    while (curr_pos != pos){
        if (curr_pos == pos){
            curr_node->item_name = item_name;
            curr_node->price = price;
            curr_node->quantity = quantity;
        }
        curr_pos++;
        curr_node = curr_node->next; 
    }
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    unsigned curr_pos = 0; 
    node* curr_node = head; 
    node* prev_node = node(); 
    while (curr_pos != pos && curr_pos->next is not None){
        if(curr_pos == pos){
            prev_node->next = curr_node->next; 
            return EXIT_SUCCESS
        }
        else{
            curr_pos++;
            prev_node = curr_node; 
            curr_node = curr_node->next; 
        }
    }
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

