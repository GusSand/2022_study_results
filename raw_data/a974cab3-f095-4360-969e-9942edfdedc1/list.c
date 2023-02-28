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
    snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    
    int count = 1;
    while(head != NULL){
        char *str = (char *)malloc(MAX_ITEM_PRINT_LEN);
        list_item_to_string(head, str);
        printf("%d: %s\n", count, str);
        count++;
        head = head->next;
    }
    return EXIT_SUCCESS;
}

// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // add a new item (name, price, quantity) to the list, such that the added item is the last item
    node *newNode = malloc(sizeof(node));
    newNode->item_name = item_name;
    newNode->price = price;
    newNode->quantity = quantity;
    newNode->next = NULL;
    if (*head == NULL){
        *head = newNode;
        return EXIT_SUCCESS;
    }
    else if (pos == 0){
        newNode->next = *head;
        *head = newNode;
        return EXIT_SUCCESS;
    }
    else{
        node *temp = *head;
        for (int i = 0; i < pos - 1; i++){
            if (temp->next == NULL){
                break;
            }
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return EXIT_SUCCESS;
    }
}
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (pos == 0){
        (*head)->item_name = item_name;
        (*head)->price = price;
        (*head)->quantity = quantity;
        return EXIT_SUCCESS;
    }
    else{
        node *temp = *head;
        for (int i = 0; i < pos - 1; i++){
            if (temp->next == NULL){
                break;
            }
            temp = temp->next;
        }
        temp->item_name = item_name;
        temp->price = price;
        temp->quantity = quantity;
        return EXIT_SUCCESS;
    }
}
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos){
    if (pos == 1){
        node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return EXIT_SUCCESS;
    }
    else{
        node *temp = *head;
        for (int i = 0; i < pos - 1; i++){
            if (temp->next == NULL){
                break;
            }
            temp = temp->next;
        }
        node *temp2 = temp->next;
        temp->next = temp2->next;
        free(temp2);
        return EXIT_SUCCESS;
    }
}
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node *temp1 = *head;
    node *temp2 = *head;
    for (int i = 0; i < pos1 - 1; i++){
        temp1 = temp1->next;
    }
    for (int i = 0; i < pos2 - 1; i++){
        temp2 = temp2->next;
    }
    node *temp3 = temp1->next;
    temp1->next = temp2->next;
    temp2->next = temp3;
    return EXIT_SUCCESS;
}
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
    node *temp = head;
    int max = 0;
    int count = 1;
    while(temp != NULL){
        if (temp->price > max){
            max = temp->price;
            *pos = count;
        }
        temp = temp->next;
        count++;
    }
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total){
    float sum = 0;
    while(head != NULL){
        sum = sum + (head->price * head->quantity);
        head = head->next;
    }
    *total = sum;
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL){
        return EXIT_FAILURE;
    }
    while(head != NULL){
        fprintf(f, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(f);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        return EXIT_FAILURE;
    }
    char item_name[100];
    float price;
    int quantity;
    int l =0;
    while(!feof(f)){
        fscanf(f, "%[^,],%f,%d\n", item_name, &price, &quantity);
        list_add_item_at_pos(head, item_name, price, quantity, l);
        l+=1;
    }
    fclose(f);
    return EXIT_SUCCESS;
}
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    return EXIT_FAILURE;
}

