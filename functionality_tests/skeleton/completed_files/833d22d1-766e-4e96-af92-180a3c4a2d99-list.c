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

    if(sprintf(str, "%i * %s @ $%.2f ea", head->quantity, head->item_name, head->price))
        return EXIT_SUCCESS;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
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
// It should not have a leading newline character.S
int list_print(node *head) {
    int i = 1;
    while(1==1) {
        if(head!=NULL) {
            char tempstr[32];
            list_item_to_string(head, tempstr);
            printf("%i: %s\n",i,tempstr);
        }
        head = head->next;
        i++;
        if(head == NULL) {
            return EXIT_SUCCESS;
        }

    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if(pos<1)
        return EXIT_FAILURE;
    else{
        while(pos--) {
            if(pos==0){
                node * temp = (node*) malloc(sizeof(node));
                temp ->  item_name = item_name;
                temp->price = price;
                temp->quantity = quantity;
                temp->next = *head;
                *head = temp;
                return EXIT_SUCCESS;
            }
            else {
                head=&(*head)->next;
            }
        }
    }
    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    unsigned int nextpos = pos+1;
    int pos2=pos+1;
    if(pos<1)
        return EXIT_FAILURE;
    else{
        while(pos--) {
            if(pos==0){
                node * temp = (node*) malloc(sizeof(node));
                temp ->  item_name = item_name;
                temp->price = price;
                temp->quantity = quantity;
                temp->next = *head;
                *head = temp;
                list_remove_item_at_pos(head, pos2);
                return EXIT_SUCCESS;
            }
            else {
                head=&(*head)->next;
            }
        }
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    node *temp = *head, *prev;
    int i = 1;
    if(temp!=NULL&&i==pos) {
        *head = temp->next;
        free (temp);
        return EXIT_SUCCESS;
    }

    while(temp!=NULL&&i!=pos) {
        prev = temp;
        temp = temp->next;
    }
    if(temp==NULL) {
        return EXIT_SUCCESS;
    }
    prev->next = temp->next;
    free(temp);
    return EXIT_SUCCESS;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if(pos1==pos2)
        return EXIT_SUCCESS;

    node *prev1 = NULL, *curr1 = *head;
    int i = 1;
    while(curr1 && i!=pos1) {
        prev1 = curr1;
        curr1 = curr1->next;
        i++;
    }
    node *prev2 = NULL, *curr2 = *head;
    i = 1;
    while(curr2 && i!=pos2) {
        prev2 = curr2;
        curr2 = curr2->next;
        i++;
    }
    if(curr1 == NULL || curr2 ==NULL) {
        return EXIT_SUCCESS;
    }
    if(prev1 != NULL) {
        prev1->next = curr2;
    }
    else{
        *head = curr2;}
    if(prev2 != NULL) {
        prev2->next = curr1;
    }
    else{
        *head = curr1;}
    node* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
    

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{

    int curr = 1;
    int high = 1;
    float val = 0;
    while(head != NULL) {
        if(head->price >val) {
            val = head->price;
            high = curr;
        }
        curr++;
        head=head->next;
    }
    *pos = high;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{

    float val = 0;
    while(head != NULL) {
        val = val + (head->price * head->quantity);
        head=head->next;
    }
    *total = val;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{

    FILE *fptr;

    fptr = fopen(filename, "w");
    while(head != NULL) {

        fprintf(fptr,"%s,%.2f,%i\n", head->item_name, head->price, head->quantity);

        head=head->next;
    }
    fclose(fptr);

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename){
    node* curr;
    curr = *head;
    node* prev;
    prev = *head;
    FILE *fptr;
    fptr = fopen(filename, "r");
    float val;
    int quant;
    int pos = 1;
    while(curr != NULL) {
        prev = curr;
        curr=curr->next;
        pos++;
    }
    while(!feof(fptr)){
        char* name = (char*) malloc(100 * sizeof(char));
        fscanf(fptr,"%[^,],%f,%d ", name, &val, &quant);
        list_add_item_at_pos(head, name, val, quant, pos);
        pos++;

    }
    
    fclose(fptr);
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    node* p1;
    node* p2;
    node* dup;
    int pos = 1;
    int pos1 = 1;
    p1 = *head;
    while(p1 != NULL && p1->next != NULL) {
        p2 = p1;
        pos = pos1;
        while(p2 != NULL && p2->next != NULL) {
            if(!strcmp(p1->item_name,p2->next->item_name)) {

                dup = p2->next;
                int sum = p1->quantity + p2->next->quantity;
                p1->quantity = p1->quantity + p2->next->quantity;


                if(dup->next == NULL){
                    p2->next=NULL;
                    break;
                }
                else {
                    p2->next=p2->next->next;
                }

                free(dup);
                break;
                
            }
            else{
                p2=p2->next;
                pos++;
            }

        }
        if(p1->next==NULL) {
            break;
        }
        else {
            p1=p1->next;
        }
        pos1++;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

