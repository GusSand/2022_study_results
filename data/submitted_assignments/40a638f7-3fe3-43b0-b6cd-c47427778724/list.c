#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
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
    if(head == NULL){
        return EXIT_FAILURE;
    }
    //node *current()    
    str =  "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price;
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
    if(head== NULL){
        return EXIT_FAILURE;
    }
    int i =1;
    node *temp = head;
    while(temp!= NULL){
        printf('%d: %d * %s @ $%.2f ea\n', i,temp->quantity,temp->item_name,temp->price);
        temp=temp->next;
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
    node *temp = *head;
    node *new_node;
    new_node = (node *)malloc(sizeof(node));
    new_node->item_name=item_name;
    new_node->price=price;
    new_node->quantity=quantity;
    if(pos ==1){
        new_node->next = temp;
        *head = new_node;
    } else {
        for(int i =1; i< pos-1; i++){
            if(temp->next==NULL){
                break;
            }
            temp= temp->next;
        }
        new_node->next=temp->next;
        temp->next=new_node;
    }
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i=1;
    node *temp = *head;
    if(pos == 1){
        temp->item_name=item_name;
        temp->price = price;
        temp->quantity = quantity;
    }else {
        for(i =1; i< pos; i++){
            if(temp == NULL){
                return EXIT_FAILURE;
            }
            temp = temp->next;
        }

        temp->item_name=item_name;
        temp->price = price;
        temp->quantity = quantity;
    }
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    
    node *temp = *head;
    if(pos == 1){
        *head = temp->next;
    } else{
        for(int i=0; i<pos-1;i++){
            temp = temp->next;
        }
        node *del =temp->next;       
        temp->next=temp->next->next;
        del->next=NULL;
    }
    return EXIT_SUCCESS;
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
    int highest = -1;
    int i = 1;
    node *temp = head;
    while(temp!=NULL){
        if(temp->price>highest){
            highest=temp->price;
            *pos =i;
        }
        temp = temp->next;
        i++;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *temp = head;
    *total = 0.00;
    while(temp!=NULL){
        *total += (temp->price * temp->quantity);
        temp = temp->next;
    }
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
    if(head ==NULL){
        return EXIT_SUCCESS;
    }
    node *temp = head;
    int fd  = open(*filename,  1);
    if(fd<0){
        return EXIT_FAILURE;
    } else{
    char* str;
        while(temp!=NULL){
            str = "%s,%.2f,%d\n", temp->item_name, temp->price, temp->quantity;
            write(fd,&str, sizeof(str));
        }
    }
    
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

