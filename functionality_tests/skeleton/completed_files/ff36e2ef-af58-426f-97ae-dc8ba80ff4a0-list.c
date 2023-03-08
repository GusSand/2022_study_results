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
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    if (head->quantity == 1) {
        sprintf(str, "%d * %s @ $%.2f each", head->quantity, head->item_name, head->price);
    } else {
        sprintf(str, "%d * %s @ $%.2f each", head->quantity, head->item_name, head->price);
    }
    return EXIT_SUCCESS;
}

// print a list to stdout

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
    char* strptr;
    int count = 0;
    node *temp = head;

    while (temp != NULL) {
        count++;
        printf("%d: ", count);
        list_item_to_string(temp, strptr);
        printf("\n");
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

// Append a new item to the end of the list.
// This 


// free all memory used by the list
int list_free(node ** n){
    if (n == NULL) {
        return EXIT_FAILURE;
    }
    node *current = *n;
    node *next;

    while (current != NULL) {
        next = current->next;
        free(current->item_name);
        free(current);
        current = next;
    }

    *n = NULL;
    return EXIT_SUCCESS;
}

// add an item to the end of the list
int list_append(node **head, char *item_name, float price)
{}

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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos){
    node *curr = *head;
    node *prev = NULL;
    node *new_item = NULL;

    new_item = malloc(sizeof(node));
    if (new_item == NULL) {
        return EXIT_FAILURE;
    }
    new_item->item_name = item_name;
    new_item->price = price;
    new_item->quantity =quantity;
    new_item->next = NULL;

    // Special cases
    if (pos == 0) {
        new_item->next = curr;
        *head = new_item;
        return EXIT_SUCCESS;
    }
    if (pos > list_length(*head)) {
        return EXIT_FAILURE;
    }

    curr = *head;
    for (unsigned int i = 0; i < pos; i++) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = new_item;
    new_item->next = curr;
    return EXIT_SUCCESS;
}

// add a new item (name, price, quantity) to the list, such that the added item
//   is the first item in the list
// For example:
// If the list is:
// 1: 3 * banana @ $1


// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node *curr = *head;
    node *prev = NULL;

    // Special cases
    if (pos == 0) {
        curr->item_name = item_name;
        curr->price = price;
        curr->quantity = quantity;
        return EXIT_SUCCESS;
    }
    if (pos > list_length(*head)) {
        return EXIT_FAILURE;
    }

    curr = *head;
    for (unsigned int i = 0; i < pos; i++) {
        prev = curr;
        curr = curr->next;
    }
    prev->item_name = item_name;
    prev->price = price;
    prev->quantity = quantity;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    node *curr = *head;
    node *prev = NULL;
    int count = 0;

    // Special cases
    if (pos == 0) {
        *head = curr->next;
        free(curr->item_name);
        free(curr);
        return EXIT_SUCCESS;
    }
    if (pos > list_length(*head)) {
        return EXIT_FAILURE;
    }

    curr = *head;
    for (unsigned int i = 0; i < pos; i++) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr->item_name);
    free(curr);
    return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node *curr = *head;
    node *prev = NULL;
    node *temp = NULL;
    int count = 0;
    // Special cases
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    else{
        *head = curr->next;
        temp = curr;
        curr = curr->next;
        temp->next = curr->next;
        curr->next = temp;
        return EXIT_SUCCESS;
    }
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    node* curr = head;
    int highest_price = curr->price;
    for (unsigned int i = 0; i < pos; i++) {
        if(curr->price > highest_price)  
            {highest_price = curr->price;}
        curr = curr->next;
    }
    return highest_price;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total){
    node *curr = head;
    while(curr != NULL){
        total += (curr->price * curr->quantity);
        curr = curr->next;
    }
    return total;
    
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{   
    
    FILE *f = fopen(strcat(filename, ".txt"), "w");
    if(f==NULL){
        printf("Error opening file");
        return EXIT_FAILURE;
    }

    node *temp = head;
    char* strptr;

    while (temp != NULL) {
        if (head == NULL) 
            {return EXIT_FAILURE;}
        fprintf(f, "%d * %s @ $%.2f each", head->quantity, head->item_name, head->price);
        temp = temp->next;
    }
    return EXIT_SUCCESS;

}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename){
    node* temp = (struct node *)malloc(sizeof(node));;
    node* head; 
    node* last; 
    last = head = NULL;
    
    FILE* file;
    file = fopen (strcat(filename, ".txt"), "r");
    if (file == NULL)
    {
        fprintf(stderr, "\nCouldn't Open File'\n");
        return EXIT_FAILURE;
    }
    
    while(fread(temp, sizeof(node), 1, file)){        
        if(head==NULL)
            {head = last = (struct node *)malloc(sizeof(node));}
        else{
            last->next = (struct node *)malloc(sizeof(node));
            last = last->next;
        }
        last->quantity = temp->quantity;
        last->price = temp->price;
        strcpy(last->item_name, temp->item_name);
        last->next = NULL;
    }
    
    fclose(file);
    return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    node *ptr1, *ptr2, *dup;
    ptr1 = head;
 
    while (ptr1 != NULL && ptr1->next != NULL) {
        ptr2 = ptr1;
        while (ptr2->next != NULL) {
            /* If duplicate then delete */
            if (strcmp(ptr1->item_name, ptr2->next->item_name)==0) {
                dup = ptr2->next;
                ptr2->next = ptr2->next->next;
                delete (dup);
            }
            else 
                {ptr2 = ptr2->next;}
        }
        ptr1 = ptr1->next;
    }
    return EXIT_SUCCESS;

}

