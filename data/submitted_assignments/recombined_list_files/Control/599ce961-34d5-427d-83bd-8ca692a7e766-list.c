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
    // bug 1: missing check for str == NULL
    if (head == NULL){
        return EXIT_FAILURE;
    }
    printf("SOmething");
    // bug 2: type confusion: mixing up char* and char
    char* quan = head->quantity + '0';
    strcat(str, quan);
    strcat(str, " * ");
    // bug 3: does not check if a item_name is NULL
    strcat(str, head->item_name);
    strcat(str, " @ $");
    char *buf;
    // bug 4: failure to initialize buf
    gcvt(head->price, 4, buf);
    strcat(str, buf);
    strcat(str, " ea");
    printf("%s", str);
    // bug 5: doesn't check that length < MAX_ITEM_PRINT_LEN
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    if (head == NULL){
        return EXIT_FAILURE;
    }
    int item = 0;
    // bug 1: infinite loop
    while(head != NULL){
        // bug 2: doesn't initialize str
        char* str;
        // bug 3: doesn't check return value of list_item_to_string
        list_item_to_string(head,str);
        printf("%d: %s\n", item, str);
    }
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    //printf("HMMM");
    node* item;
    //node* temp = &(*head);
    // bug 2: use of uninitialized variable item
    item->item_name = item_name; // bug 3: missing strdup
    item->price = price;
    item->quantity = quantity;
    //unsigned int counter = 0;
    if (*head == NULL){
        *head = item;
        return EXIT_SUCCESS;
    }
    while(pos > 1){
        *head = (*head)->next; // bug 4: memory leak by overwriting head pointer
        
        //printf("Counter: %d\n", counter);
        pos--;
    }
    // bug 5: missing check for next == NULL
    item->next = (*head)->next;
    (*head)->next =  item;
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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
    return EXIT_FAILURE;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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


