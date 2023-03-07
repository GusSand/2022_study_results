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
    // bug 1: id-220, omitted, codex, missing check for str == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        str = "";
        return EXIT_FAILURE;
    }
    node *current = head;
    while (current != NULL) {
        // bug 2: id-221, omitted, codex, does not check if a item_name is NULL before print
        // bug 3: id-222, present, codex, Use of sprintf instead of snprintf for str with MAX_LEN
        sprintf(str, "%d * %s @ $%.2f ea", current->quantity, current->item_name, current->price);
        current = current->next;
    }
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        printf("\n");
        return EXIT_FAILURE;
    }
    node *current = head;
    int pos = 1;
    while (current != NULL) {
        // bug 1: id-339, omitted, humanf, does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n", pos, current->quantity, current->item_name, current->price);
        current = current->next;
        pos++;
    }
    return EXIT_SUCCESS;

}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    if(pos == 1){
        node *new_node = malloc(sizeof(node));
        // bug 1: id-79, present, approx-0.49, missing strdup
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = current;
        *head = new_node;
    }else{
        int i;
        for (i = 1; i < (pos - 1); i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        node *new_node = malloc(sizeof(node));
        // bug 2: id-79, present, approx-0.34, missing strdup
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = current->next;
        current->next = new_node;
    }
    return EXIT_SUCCESS;

}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    // bug 1: id-455, omitted, approx-0.43, missing check for *head == NULL
    if(pos == 1){
        // bug 2: id-453, omitted, humanf, missing free
        // bug 3: id-454, present, approx-0.43, missing strdup
        current->item_name = item_name;
        current->price = price;
        current->quantity = quantity;
    }else{
        int i;
        for (i = 1; i < pos; i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        // bug 4: id-453, omitted, human, missing free
        // bug 5: id-454, present, human, missing strdup
        current->item_name = item_name;
        current->price = price;
        current->quantity = quantity;
    }
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    // bug 1: id-552, omitted, humanf, missing check for *head == NULL
    node *current = *head;
    if(pos == 1){
        *head = current->next;
        // bug 2: id-551, omitted, humanf, missing free of item_name
        free(current);
    }else{
        int i;
        for (i = 1; i < (pos - 1); i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        node *temp = current->next;
        current->next = temp->next;
        free(temp);
        // bug 3: id-551, omitted, humanf, missing free of item_name
    }
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    // bug 1: id-711, omitted, humanf, missing check for *head == NULL
    node *current = *head;
    node *current1 = current;
    node *current2 = current;
    int i;
    for (i = 1; i < pos1; i++){
        if(current->next == NULL){
            break;
        }
        current = current->next;
    }
    current1 = current->next;
    for (i = 1; i < pos2; i++){
        if(current->next == NULL){
            break;
        }
        current = current->next;
    }
    current2 = current->next;
    current->next = current2;
    current2->next = current1;
    current1->next = current2->next;
    // bug 2: id-710, present, unknown, memory leak (loses nodes)
    // bug 3: id-712, present, unknown, infinite loop
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == NULL){
        return EXIT_FAILURE;
    }
    if(head->next == NULL){
        *pos = 1;
        return EXIT_SUCCESS;
    }
    node *current = head;
    int i = 1;
    float max = 0.0;
    while (current != NULL) {
        if(current->price > max){
            max = current->price;
            *pos = i;
        }
        current = current->next;
        i++;
    }
    return EXIT_SUCCESS;
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
    if(head!=NULL){
        
        return EXIT_SUCCESS;
    }
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


