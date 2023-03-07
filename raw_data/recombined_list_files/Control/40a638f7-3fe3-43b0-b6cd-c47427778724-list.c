#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

#include "reflist.h"

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    if(head == NULL){
        return EXIT_FAILURE;
    }
    //node *current()    
    str =  "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price;
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head== NULL){
        return EXIT_FAILURE;
    }
    int i =1;
    node *temp = head;
    while(temp!= NULL){
        // bug 1: wrong arguments to printf (single rather than double quote)
        // bug 2: does not check if a item_name is NULL before print
        printf('%d: %d * %s @ $%.2f ea\n', i,temp->quantity,temp->item_name,temp->price);
        temp=temp->next;
        i++;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    node *temp = *head;
    node *new_node;
    new_node = (node *)malloc(sizeof(node));
    new_node->item_name=item_name; // bug 2: missing strdup
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

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    int i=1;
    node *temp = *head;
    if(pos == 1){
        // bug 3: missing free
        // bug 4: missing strdup
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

        // bug 5: missing free
        // bug 6: missing strdup
        temp->item_name=item_name;
        temp->price = price;
        temp->quantity = quantity;
    }
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    node *temp = *head;
    if(pos == 1){
        *head = temp->next;
    } else{
        // bug 3: missing check for next == NULL
        for(int i=0; i<pos-1;i++){
            temp = temp->next;
        }
        node *del =temp->next;       
        temp->next=temp->next->next;
        del->next=NULL;
        // bug 4: missing free of item
        // bug 5: missing free of item_name
    }
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    return EXIT_FAILURE;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for pos == NULL
    // bug 2: int vs float confusion
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

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *temp = head;
    // bug 1: missing check for total == NULL
    *total = 0.00;
    while(temp!=NULL){
        *total += (temp->price * temp->quantity);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head ==NULL){
        return EXIT_SUCCESS;
    }
    node *temp = head;
    // bug 1: type confusion char* vs char
    int fd  = open(*filename,  1);
    if(fd<0){
        return EXIT_FAILURE;
    } else{
    char* str;
        while(temp!=NULL){
            str = "%s,%.2f,%d\n", temp->item_name, temp->price, temp->quantity;
            // bug 3: char ** vs char* confusion
            // bug 4: sizeof pointer
            // bug 5: missing check for write failure
            write(fd,&str, sizeof(str));
        }
    }
    // bug 2: missing close() leaks file descriptor
    
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    return EXIT_FAILURE;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}


