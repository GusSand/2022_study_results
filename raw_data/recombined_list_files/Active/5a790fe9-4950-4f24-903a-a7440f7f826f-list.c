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
    // bug 1: id-183, omitted, unrecorded, missing check for str == NULL / head == NULL
    // bug 2: id-185, omitted, unrecorded, missing check for item_name == NULL
    // bug 3: id-186, omitted, unrecorded, mixing up char * and status code
    // bug 4: id-184, present, unrecorded, sprintf with no buffer provided
    str = sprintf("%d. %d * %s @ $%f ea", head->quantity, head->item_name, head->price);
    return EXIT_FAILURE;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    //node ptr = head;
    //int i = 1;
    if(head == NULL){
        return EXIT_FAILURE;
    }
    while (head != NULL)
    {
       // bug 1: id-322, omitted, unrecorded, does not check if a item_name is NULL before print
       // bug 2: id-321, present, unrecorded, incorrect number of format strings vs arguments
       printf("%d. %d * %s @ $%f ea", head->quantity, head->item_name, head->price);
        head = head->next;
    }
    
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-49, present, unrecorded, type confusion, head should be *head
    // bug 2: id-48, omitted, unrecorded, missing NULL check on head
    node *ptr = head;
    if (pos < 1){
        return EXIT_FAILURE;
    }
    if (pos == 1){
        // bug 3: id-46, omitted, unrecorded, failure to initialize newnode
        node *newnode;
        // bug 9: id-45, present, unrecorded, missing strdup
        newnode->item_name = item_name;
        newnode->price = price;
        newnode->quantity = quantity;
        // bug 5: id-44, present, unrecorded, memory leak
        newnode->next = ptr->next;
        // bug 6: id-49, present, unrecorded, type confusion, should be *head
        head = newnode;
    }
    if(pos != 1){
        // bug 8: id-47, omitted, unrecorded, missing check for next == NULL
        while(pos-- != 0) {
            if (pos == 1){
                // bug 4: id-46, omitted, unrecorded, failure to initialize newnode
                node *newnode;
                // bug 10: id-45, present, unrecorded, missing strdup
                newnode->item_name = item_name;
                newnode->price = price;
                newnode->quantity = quantity;
                newnode->next = ptr->next;
                ptr->next = newnode;
                break;
            }
            // bug 7: id-49, present, unrecorded, type confusion, should be *head
            head = ptr->next;
        }
        if(pos != 1){
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-416, present, unrecorded, type confusion on head vs *head
    node *ptr = head;
    int i = 0;
    if(pos < 0){
        return EXIT_FAILURE;
    }
    // bug 2: id-414, omitted, unrecorded, missing check for next == NULL
    // bug 3: id-416, omitted, unrecorded, missing check for *head == NULL
    // bug 4: id-415, omitted, unrecorded, missing check for head == NULL
    while(i != pos){
        i++;
        ptr = ptr->next;
    }
    ptr->quantity = quantity;
    // bug 5: id-412, omitted, unrecorded, missing free
    // bug 6: id-413, present, unrecorded, missing strdup
    ptr->item_name = item_name;
    ptr->price = price;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-526, omitted, unrecorded, missing check for head == NULL
    // bug 2: id-527, present, unrecorded, type confusion, *head vs head
    node *ptr = head;
    int i = 0;
    if(pos < 0){
        return EXIT_FAILURE;
    }
    while(i != pos-1){
        i++;
        ptr = ptr->next;
        // bug 3: id-525, omitted, unrecorded, missing check for next == NULL
    }
    ptr->next = ptr->next->next;
    // bug 4: id-524, omitted, unrecorded, missing free of item
    // bug 5: id-523, omitted, unrecorded, missing free of item_name
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 0;
    int j =0;
    // bug 1: id-693, present, unrecorded, type confusion head vs *head
    node *n1 = head;
    node *n2 = head;
    node *n1prev = head;
    node *n2prev = head;
    node *temp;
    if(pos1 == pos2){
        return EXIT_SUCCESS;
    }
    if(pos1 <0 || pos2 <0){
        return EXIT_FAILURE;
    }
    while (i != pos1){
        i++;
        n1prev = n1;
        // bug 2: id-692, omitted, unrecorded, missing check for next == NULL
        n1 = n1->next;
    }
    while (j != pos2){
        j++;
        n2prev = n2;
        // bug 3: id-692, omitted, unrecorded, missing check for next == NULL
        n2 = n2->next;
    }
    // bug 4: id-692, omitted, unrecorded, missing check for next == NULL
    n1prev->next = n2;
    n2prev->next = n1;
    temp  = n2->next;
    n2->next = n1->next;
    n1->next = temp;

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i=0;
    float max=0;
    while (head != NULL)
    {
        if(head->price > max){
            max = head->price;
            // bug 1: id-615, present, unrecorded, type confusion int * vs int
            pos = i;
        }
        i++;
        head = head->next;
    }
    
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    float cost = 0;
    // bug 1: id-655, present, unrecorded, infinite loop
    while(head != NULL){
        cost = cost + ((float)head->quantity * head->price);
    }
    // bug 2: id-654, omitted, unrecorded, missing check for total == NULL
    *total = cost;
    return EXIT_SUCCESS;
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


