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
    // bug 2: does not check if a item_name is NULL before print
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 4: missing check for head == NULL
    int res = sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    if(res < 0)
        return EXIT_FAILURE;
    // TODO: Implements this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    node* current = head;
    // bug 1: wrong calculation of buffer size
    char* current_string = malloc(sizeof(MAX_ITEM_PRINT_LEN));
    int res, i=1;
    while(current != NULL){
        res = list_item_to_string(current,current_string);
        if(res == EXIT_FAILURE)
            return EXIT_FAILURE;
        printf("%d: %s\n", i, current_string);
        current = current->next;
        i++;
    }
    // bug 2: memory leak on current_string
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    // create new element
    node* new_node = (node*) malloc(sizeof(node));
    new_node->item_name = item_name; // bug 3: missing strdup
    new_node->price = price;
    new_node->quantity = quantity;
    // bug 4: doesn't initialize next pointer

    if(*head == NULL){
        // printf("first element at %p", *head);
        *head = new_node;
        return EXIT_SUCCESS;
    }
    int current_pos = 1;
    node* pointer = *head;
    while(current_pos < pos-1){
        pointer = pointer->next;
        if(pointer == NULL)
            return EXIT_FAILURE; // bug 2: memory leak on EXIT_FAILURE
        
        current_pos++;
    }
    node* before = pointer;
    node* after = pointer->next;

    before->next = new_node;
    new_node->next = after;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    node* current = *head;
    int current_pos = 1;
    while(current_pos < pos){
        current = current->next;
        if(current == NULL)
            return EXIT_FAILURE;
        current_pos++;
    }

    // bug 3: missing free
    // bug 4: missing strdup
    current->item_name = item_name;
    current->price = price;
    current->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    node* current = *head;
    int current_pos = 1;
    if(pos == 1){
        free(*head);
        // bug 2: memory leak by overwriting head pointer
        // bug 3: missing free of item_name

        *head = NULL;
        return EXIT_SUCCESS; 
    }
    while(current_pos < pos - 1){
        // bug 4: missing check for *head == NULL
        current = current->next;
        if(current->next == NULL)
            return EXIT_FAILURE;
        current_pos++;
    }
    node* before = current;
    node* to_remove = current->next;
    node* after = to_remove->next;

    before->next = after;
    free(to_remove);
    // bug 5: missing free of item_name
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    node* current = *head;
    int current_pos = 1;
    while(current_pos < pos1){
        // bug 3: missing check for next == NULL
        current = current->next;
        current_pos++;
    }

    char* temp_item_name = current->item_name;
    float temp_price = current->price;
    int temp_quantity = current->quantity;

    current_pos = 1;
    current = *head;
    while(current_pos < pos2){
        // bug 4: missing check for next == NULL
        current= current->next;
        current_pos++;
    }

    node* node2 = current;

    int res = list_update_item_at_pos(head, node2->item_name, node2->price, node2->quantity, pos1);
    if(res == EXIT_FAILURE)
        return EXIT_FAILURE;
    res = list_update_item_at_pos(head, temp_item_name, temp_price, temp_quantity, pos2);
    if(res == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // bug 1: missing check for head == NULL
    node* current = head;
    float max_price = head->price;
    int current_pos = 1;
    // bug 2: missing check for pos == NULL
    *pos = 1;
    while(current != NULL){
        if(current->price > max_price){
            *pos = current_pos;
        }
        current_pos ++;
        current = current->next;
    }
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    node* current = head;
    while(current != NULL){
        // bug 1: missing check for total == NULL
        *total += current->price * current->quantity;
        current = current->next;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // bug 1: missing check for filename == NULL
    FILE* fptr = fopen(filename, "a");
    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    node* current = head;

    while(current != NULL){
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(fptr, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }
    
    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // bug 1: missing check for filename == NULL
    FILE* fptr = fopen(filename, "r");
    // bug 2: missing check for head == NULL
    node* current = *head;
    int pos = 1;

    // bug 3: buffer overflow from fixed-size item name
    char* item_name = malloc(MAX_ITEM_PRINT_LEN);
    float *price = malloc(sizeof(float));
    int *quantity = malloc(sizeof(int));

    while(current != NULL && current->next != NULL){
        current = current->next;
        pos++;
        if(current->next == NULL)
            pos++;
    }
    
    int res;
    // bug 4: fscanf may not set all values
    while(fscanf(fptr, "%s,%f,%d", item_name, price, quantity) != EOF){
        res = list_add_item_at_pos(head, item_name, *price, *quantity, (unsigned int) pos);
        if (res == EXIT_FAILURE)
            return EXIT_FAILURE;
        pos++;
        
    }
    free(item_name);
    free(price);
    free(quantity);
    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // bug 1: missing check for head == NULL
    node* current = *head;
    node* next;
    int pos1 = 1, pos2= 2;
    // bug 2: infinite loop
    while(current != NULL && current->next != NULL){
        node* second_ptr = current->next;
        while(second_ptr != NULL ){
            if(current->item_name == second_ptr->item_name){
                int total_quantity = current->quantity + second_ptr->quantity;
                
            }
            pos2++;
        }
        pos1++;
    }
    return EXIT_FAILURE;
}


