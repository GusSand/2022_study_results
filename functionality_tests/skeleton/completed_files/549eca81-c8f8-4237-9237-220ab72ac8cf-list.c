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
    if(head == NULL){ return EXIT_FAILURE; }
    int i = snprintf(str, MAX_ITEM_PRINT_LEN, "%u * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
    //return EXIT_FAILURE;
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
    char buffer[MAX_ITEM_PRINT_LEN];
    if(head == NULL){ return EXIT_FAILURE; }
    node *curr = head;
    while(curr != NULL){
        list_item_to_string(curr, buffer);
        printf("%s\n", buffer);
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

    node *nnode = malloc(sizeof(node));
    nnode->item_name = item_name;
    nnode->price = price;
    nnode->quantity = quantity;
    if(pos == 1){
        nnode->next = *head;
    }
    else{
        node *curr = *head;
        for(unsigned int i = 2; i < pos; i++){
            if (curr == NULL){
                return EXIT_FAILURE; //list shorter than pos
            }
            curr = curr->next;
        }
        nnode->next = curr->next;
        curr->next = nnode;
    }
    *head = nnode;
    return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node *curr = *head;
    for(unsigned int i = 1; i < pos; i++){
        if(curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    if(pos == 1){
        node *temp = *head;
        *head = temp->next;
        free(temp);
        return EXIT_SUCCESS;
    }
    else{
        node *curr = *head;
        for(int i = 2; i < pos; i++){
            if( curr == NULL ){ return EXIT_FAILURE; }
            curr = curr->next;
        }
        if(curr->next == NULL){ return EXIT_FAILURE; }
        node *temp = curr->next;
        curr->next = curr->next->next;
        free(temp);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos1 == pos2){return EXIT_SUCCESS;}
    if(pos1 > pos2){int t = pos1; pos1=pos2; pos2=t;}
    if(pos1 < 1){return EXIT_FAILURE;}
    node *p1;
    node *p2;

    node *curr = *head;
    for(int i = 1; i < pos2-1; i++){
        if (curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    p2 = curr;
    if(pos1 == 1){
        p2->next = *head;
        *head = p2;
        
    }
 
 
    curr = *head;
    for(int i = 2; i < pos1-1; i++){
        if (curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    p1 = curr;



    //if(p2->next == NULL){return EXIT_FAILURE;}
    
    if(pos2-pos1 == 1){
        node *t = p2->next->next;
        p1->next = p2->next;
        p2->next->next = p2;
        p2->next = t;
    }
    else{
        node *t = p1->next;
        p1->next = p2->next;
        p2->next = t;
        t = p1->next->next;
        p1->next->next = p2->next->next;
        p2->next->next = t;
    }
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    //segfaults while commented and unable to debug
    // if(head == NULL){
    //     return EXIT_FAILURE;
    // }
    // int ind = 1;
    // int mpos = 1;
    // float max = 0;
    // node *d = head;
    // while(d != NULL){
    //     if(d->price > max){
    //         mpos = ind;
    //         max = d->price;
    //     }
    //     d = d->next;
    //     ind += 1;
    // }
    // return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    float tot = 0;
    node *curr = head;
    while(curr != NULL){
        tot += curr->price;
        curr = curr->next;
    }
    *total = tot;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n a
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE *fptr = fopen(filename, "w");
    char buf [100];
    node *curr = head;
    while(curr != NULL){
        int i = snprintf(buf, 100, "%s,%.2f,%d\n",head->item_name, head->price, head->quantity);
        fputs(buf, fptr);
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    FILE *fptr = fopen(filename, "r");
    char buf [100];
    int pos = 1;
    while(fgets(buf, 100, fptr) != NULL){
        char t[100];
        strcpy(t,buf);
        char *pt;
        pt = strtok(t, ",");
        char *name = pt;
        pt = strtok(t, ",");
        float price = atof(pt);
        pt = strtok(t, ",\n");
        int quantity = atoi(pt);

        list_add_item_at_pos(head, name, price, quantity, pos);
        pos ++;
    }


    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    node *curr = *head;
    while(curr != NULL){
        node *c2 = curr;
        while(c2->next != NULL){
            if(c2->next->item_name == curr->item_name && c2->next->price == curr->price){
                curr->quantity += c2->next->quantity;
                node *t = c2->next;
                c2->next = c2->next->next;
            }
            c2 = c2->next;
        }
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

