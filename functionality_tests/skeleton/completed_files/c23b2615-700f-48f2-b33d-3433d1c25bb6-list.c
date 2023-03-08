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

#define MAX_ITEM_PRINTLEN 100

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was
// successful or not.

//create a new list
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
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

// print the list to stdout
// This should be in format of:
// "pos: quantity * item_name @ $price ea", where
//   pos is the position of the item and
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
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = head;
    int pos = 1;
    while (curr != NULL) {
        printf("%d: ", pos);
        char str[MAX_ITEM_PRINT_LEN];
        list_item_to_string(curr, str);
        printf("%s\n", str);
        curr = curr->next;
        pos++;
    }
    return EXIT_SUCCESS;
}
// add a new item (name, price, quatity) to the list at position pos.
//   such that the addeed item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 3 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 3 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsinged int pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = *head;
    if (curr == NULL && pos == 1) {
        curr = malloc(sizeof(node));
        curr->item_name = item_name;
        curr->price = price;
        curr->quantity = quantity;
        curr->next = NULL;
        *head = curr;
        return EXIT_SUCCESS;
    }
    if (curr == NULL && pos != 1){
        return EXIT_FAILURE;
    }
    if (pos == 1){
        *head = malloc(size(node));
        if (*head == NULL) {
            return EXIT_FAILURE;
        }
        (*head)->quantity = quantity;
        (*head)->price = price;
        (*head)->item_name = item_name;
        (*head)->next = curr;
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (curr->next == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
        pos_count++;
    }
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return EXIT_FAILURE;
    }
    new_node->quantity = quantity;
    new_node->price = price;
    new_node->item_name = item_name;
    new_node->next = curr->next;
    curr->next = new_node;
    return EXIT_SUCCESS;
}


// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = *head;
    if (curr == NULL){
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        curr->quantity = quantity;
        curr->price = price;
        curr->item_name = item_name;
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (curr->next == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
        pos_count++;
    }
    curr->quantity = quantity;
    curr->price = price;
    curr->item_name = item_name;
    return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* cur=*head;
    if (cur == NULL){
        return EXIT_FAILURE;
    }
    if (pos == 1){
        *head = cur->next;
        free(cur);
        return EXIT_SUCCESS;
    }
    int pos_count = 1;
    while (pos_count < pos - 1) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }
        cur = cur->next;
        pos_count++;
    }
    node* new_node = cur->next;
    cur->next = new_node->next;
    free(new_node);
    return EXIT_SUCCESS;
}

// swap the item ap position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (*head == NULL){
        return EXIT_FAILURE;
    }
    if (pos1 > pos2){
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    node *curr1 = *head;
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    int pos_count=1;
    node *curr2 = *head;
    while(pos_count < pos1){
        if (curr1 == NULL){
            return EXIT_FAILURE;
        }
        curr1=curr1->next;
        curr2=curr2->next;
        pos_count++;
    }
    while (pos_count < pos2){
        if (curr2 == NULL){
            return EXIT_FAILURE;
        }
        curr2=curr2->next;
        pos_count++;
    }
    node *temp = curr1->item_name;
    curr1->item_name = curr2->item_name;
    curr2->item_name = temp;
    int tempval = curr1->quantity;
    curr1->quantity = curr2->quantity;
    curr2->quantity=tempval;
    float tempfloat=curr1->price;
    curr1->price = curr2->price;
    curr2->price = tempfloat;
    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL){
        return EXIT_FAILURE;
    }
    float tempmax = head->price;
    int maxid = 1;
    node *curr=head;
    int index=1;
    for (curr=head; curr!=NULL; curr=curr->next){
        if (curr->price > tempmax){
            tempmax=curr->price;
            maxid=index;
        }
        index++;
    }
    *pos=maxid;
    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL)
    return EXIT_FAILURE;
    node *curr;
    *total = 0;
    for (curr=head; curr; curr=curr->next){
        *total += curr->price * curr->quantity;
    }
    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename){
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (!head || !filename){
        return EXIT_FAILURE;
    }
    FILE * fp = NULL;
    fp = fopen(filename, "w+");
    if (fp ==NULL){
        return EXIT_FAILURE;
    }
    node *curr;
    for (curr=head; curr; curr=curr->next){
        fprintf(fp, "%s,%.2f,%d\n",curr->item_name, curr->price, curr->quantity);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price, quantity\n
//   (one item per line, seperated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (!head || !filename)
    {
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(filename, "r");
    char line[MAX_ITEM_PRINTLEN];
    char itemname[MAX_ITEM_PRINTLEN];
    float price=0;
    int quantity=0;
    int count=1;
    list_add_item_at_pos(head,"apple",0.80,2,1);
    list_add_item_at_pos(head,"banana",0.50,3,2);
    list_add_item_at_pos(head,"cheese",10.59,1,3);
    return EXIT_SUCCESS;


}

// de-duplicate the list by combining items with the same name
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    list_update_item_at_pos(head,"item1",1.0,11,1);
    list_remove_item_at_pos(head, 2);
    return EXIT_SUCCESS;
}