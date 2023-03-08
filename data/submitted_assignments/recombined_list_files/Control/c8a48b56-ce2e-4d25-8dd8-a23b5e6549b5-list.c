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
    // TODO: Implement this function, 

    if (head != NULL){
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    }
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    node* cur;
    cur = head;
    int i = 0;
    while (cur != NULL){
        i++;
        // bug 1: does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n",i,cur->quantity,cur->item_name,cur->price);
        cur = cur->next;
    }
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    node* cur = *head;
    node* prev = NULL;
    for (int i=1; i<pos; i++){
        prev = cur;
        cur = cur->next; // bug 2: missing check for next == NULL
        // bug 3: missing check for *head == NULL
    }
    node* new_node = malloc(sizeof(node));
    if (pos==1){
        
        new_node->next = *head;
        *head = new_node;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->item_name = item_name; // bug 4: missing strdup
        return EXIT_SUCCESS;
    }
    new_node->next = prev->next;
    prev->next = new_node;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->item_name = item_name; // bug 5: missing strdup
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    // bug 3: missing check for *head == NULL
    node* cur = *head;
    for (int i=1; i<pos; i++){
        cur = cur->next;
    }
    cur->price = price;
    cur->quantity = quantity;
    // bug 4: missing free
    // bug 5: missing strdup
    cur->item_name = item_name;
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    node *cur = *head;
    node *prev, *temp;
    if (pos==1){
        temp = *head;
        *head = temp->next;
        temp = NULL;
        // bug 3: missing free of item
        // bug 4: missing free of item_name
        return EXIT_SUCCESS;
    }
    for (int i=1; i<pos; i++){
        prev = cur;
        cur = cur->next;
        // bug 5: missing check for next == NULL
    }

    prev->next = cur->next;
    // bug 6: missing free of item
    // bug 7: missing free of item_name
    cur = NULL;
    
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // bug 1: missing check for head == NULL
    int mind, maxd;
    if (pos1<=pos2){mind = pos1; maxd = pos2;}
    else {mind = pos2; maxd = pos1;}

    node* min = *head;
    node* max = *head;
    node* temp = *head;
    int i=1;

    while (temp != NULL){        
        if(i==mind){
            max = temp;
            for (int j=i; j<maxd; j++){
                // bug 2: missing check for next == NULL
                max = max->next;}
            temp = min;
            min->next = max->next;
            max->next = temp->next;          
        }
        i++;
        temp = temp->next;
    }
    // bug 3: memory leak failing to update *head
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // bug 2: int vs float confusion
    int max = -10000;
    int max_ind;
    // bug 1: failed to initialize cur
    node* cur;
    cur->next = head;
    int i = 0;
    while (1){       
        if (cur == NULL){
            break;
        }
        if (cur->price >= max){
            max = cur->price;
            max_ind = i;
        }
        i++;
        cur = cur->next;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    node* cur;
    cur = head;
    // bug 1: int vs float confusion
    int cost = 0;

    while (1){
        if (cur == NULL){
            break;
        }
        cost += cur->price * cur->quantity;
        cur = cur->next;
    }
    // bug 2: missing check for total == NULL
    *total = cost;
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    node* cur;
    cur = head;
    // bug 1: missing check for filename == NULL
    FILE *file;
    file = fopen(filename, "w");
    while(cur != NULL){
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(file, "%d,%s,%.2f", cur->quantity, cur->item_name, cur->price);
        cur = cur->next;
    }

    // bug 4: missing fclose
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
} 

int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    node* cur;
    // bug 1: missing check for head == NULL
    cur = *head;
    while(cur != NULL){
        cur = cur->next;
    }

    FILE *file;
    // bug 2: missing check for filename == NULL
    file = fopen(filename, "w");
    while(cur != NULL){
        // bug 3: potential buffer overflow on cur->item_name
        fscanf(file, "%d,%s,%f", &cur->quantity, cur->item_name, &cur->price);
        cur = cur->next;
    }
    // bug 4: fails to call fclose
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // bug 1: missing check for head == NULL
    node* cur = *head;
    node* prev = cur;
    
    // bug 2: potential buffer overflow if list is longer than 10000
    const char* item_list[10000];
    int flag=0;

    int i=0;
    while (1){
        if(cur == NULL){
            break;
        }
        else{
            item_list[i] = cur->item_name;

        }
        for (int j=0; j<i; j++){
            // bug 3: use of uninitialized variable
            if (cur->item_name == item_list[j]){
                flag=1;
            }
        }
        if(flag){
            //prev unchanged
            cur = cur->next;           
            i++;
        }
        else{
            prev = cur;
            cur = cur->next;
            i++;
        }

    }
    // bug 4: missing check for cursor NULL
    node* fut = cur->next;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}


