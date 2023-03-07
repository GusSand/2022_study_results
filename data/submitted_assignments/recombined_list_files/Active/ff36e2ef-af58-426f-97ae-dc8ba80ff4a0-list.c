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
    // bug 1: id-289, omitted, human, missing check for str == NULL
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    if (head->quantity == 1) {
        // bug 2: id-290, omitted, approx-0.44, does not check if a item_name is NULL before print
        // bug 3: id-291, present, approx-0.44, Use of sprintf instead of snprintf for str with MAX_LEN
        sprintf(str, "%d * %s @ $%.2f each", head->quantity, head->item_name, head->price);
    } else {
        // bug 4: id-290, omitted, approx-0.44, does not check if a item_name is NULL before print
        // bug 5: id-291, present, approx-0.44, Use of sprintf instead of snprintf for str with MAX_LEN
        sprintf(str, "%d * %s @ $%.2f each", head->quantity, head->item_name, head->price);
    }
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // bug 1: id-377, omitted, human, failed to initialize strptr
    char* strptr;
    int count = 0;
    node *temp = head;

    while (temp != NULL) {
        count++;
        printf("%d: ", count);
        // bug 2: id-376, omitted, approx-0.10, doesn't check return value of list_item_to_string
        list_item_to_string(temp, strptr);
        printf("\n");
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
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
    // bug 1: id-736, omitted, human, missing check for head == NULL
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
        // bug 2: id-737, omitted, approx-0.30, missing/wrong check for next == NULL
        temp->next = curr->next;
        curr->next = temp;
        return EXIT_SUCCESS;
    }
}

int list_find_highest_price_item_position(node *head, int *pos) {
    // bug 1: id-642, omitted, human, missing check for head == NULL
    node* curr = head;
    // bug 2: id-643, present, human, int vs float confusion
    int highest_price = curr->price;
    // bug 3: id-644, present, human, int vs int* confusion
    for (unsigned int i = 0; i < pos; i++) {
        if(curr->price > highest_price)  
            {highest_price = curr->price;}
        curr = curr->next;
    }
    // bug 4: id-641, present, human, return of wrong status code
    return highest_price;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_save(node *head, char *filename)
{   
    // bug 1: id-866, present, human, possible buffer overflow on filename
    // bug 2: id-864, omitted, human, missing check for filename == NULL
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
        // bug 3: id-862, omitted, approx-0.30, missing check for fprintf failure
        // bug 4: id-865, omitted, human, missing check for item_name == NULL
        fprintf(f, "%d * %s @ $%.2f each", head->quantity, head->item_name, head->price);
        temp = temp->next;
    }
    // bug 5: id-863, omitted, human, missing fclose
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


