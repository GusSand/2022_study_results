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
    while(*head !=NULL){
        head=&(*head)->next;
    }

    *head=malloc(sizeof(node));
    if(*head==NULL)
        return EXIT_FAILURE;
    (*head)->str =malloc(strlen(str)+1);
    if((*head)->item_name==NULL)
        return EXIT_FAILURE;
    strcpy((*head)->item_name,str);
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
    if(head==NULL){
        return EXIT_FAILURE;
    }
    struct node *curr=head;
    int pos=0;
    while(curr!=NULL){
        pos=pos+1;
        printf("%d: %d * %s @ $%.2f ea\n", pos, curr->quantity,curr->item_name,curr->price);
        curr=curr->next;
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
    struct node *temp,*ptr;
    temp=(struct node*) malloc(sizeof(struct node));
    &temp->item_name=item_name;
    &temp->price=price;
    &temp->quantity=quantity;
    temp->next=NULL;
    if(pos==0)
    {
        temp->next=head;
        head=temp;
    }
    else
    {
        for(i=0;ptr=head;i<pos-1;i++){
            ptr=ptr->next;
            if(ptr==NULL)
            {
                return EXIT_FAILURE;
            }
        }
        temp->next=ptr->next;
        ptr->next=temp;
    }
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    struct node *ptr;

    for(i=0,ptr=head;i<pos-1;i++){
        ptr=ptr->next;
        if(ptr==NULL)
        {
            return EXIT_FAILURE;
        }
    }
    &ptr->item_name=item_name;
    &ptr->price=price;
    &ptr->quantity=quantity;

    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    int i=0;
    char* in="";
    float p=-1;
    int q=-1;
    node *current=*head;
    node *temp_node=NULL;
    if(pos==0){
        return pop(head);
    }
    for(i=0;i<pos-1;i++){
        if(current->next==NULL){
            return -1;
        }
        current=current->next;
    }
    if (current->next==NULL){
        return -1;
    }
    temp_node=current->next;
    in=temp_node->item_name;
    p=temp_node->price;
    q=temp_node->quantity;
    current->next=temp_node->next;
    free(temp_node);

    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    struct node *node1, *node2, *prev1, *prev2, *temp;
    int i;

    // Get the far position among both
    const int maxPos = (pos1 > pos2) ? pos1 : pos2;

    // Get total nodes in the list
    const int totalNodes = count(head);

    // Validate swap positions
    if ((pos1 <= 0 || pos1 > totalNodes) || (pos2 <= 0 || pos2 > totalNodes))
    {
        return EXIT_FAILURE;
    }
    
    // If both positions are same then no swapping required
    if (pos1 == pos2)
    {
        return EXIT_SUCCESS;
    }


    // Identify both nodes to swap
    i = 1;
    temp  = head;
    prev1 = NULL;
    prev2 = NULL;

    // Find nodes to swap
    while (temp != NULL && (i <= maxPos))
    {
        if (i == pos1 - 1)
            prev1 = temp;
        if (i == pos1)
            node1 = temp;

        if (i == pos2 - 1)
            prev2 = temp;
        if (i == pos2)
            node2 = temp;

        temp = temp->next;
        i++;
    }

    // If both nodes to swap are found.
    if (node1 != NULL && node2 != NULL)
    {
        // Link previous of node1 with node2
        if (prev1 != NULL)
            prev1->next = node2;

        // Link previous of node2 with node1
        if (prev2 != NULL)
            prev2->next = node1;

        // Swap node1 and node2 by swapping their 
        // next node links
        temp= node1->next;
        node1->next = node2->next;
        node2->next = temp;

        // Make sure to swap head node when swapping
        // first element.
        if (prev1 == NULL)
            head = node2;
        else if (prev2 == NULL)
            head = node1;
    }
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    if(head==NULL){
        return EXIT_FAILURE;
    }
    struct node *curr=head;
    int max=0;
    int place=1
    while(curr!=NULL){
        if (curr->price >= max){
            max=curr->price;
            pos=place;
        }
        place=place+1;
        curr=curr->next;
    }

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    if(head==NULL){
        return EXIT_FAILURE;
    }
    struct node *curr=head;
    while(curr!=NULL){
        total->(curr->price)*(curr->quantity);
        curr=curr->next;
    } 
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE * fptr;
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

