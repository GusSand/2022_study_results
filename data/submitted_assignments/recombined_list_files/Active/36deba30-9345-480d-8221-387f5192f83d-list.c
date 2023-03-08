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
    if(head == NULL)
    {
        //printf("head is NULL\n");
        return EXIT_FAILURE;
    }
    // bug 1: id-163, omitted, human, missing check for str == NULL
    // bug 2: id-164, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-165, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = head;
    char str[MAX_ITEM_PRINT_LEN];
    while (curr != NULL) {
        // bug 1: id-304, omitted, approx-0.36, doesn't check return value of list_item_to_string
        list_item_to_string(curr, str);
        // bug 2: id-305, omitted, approx-0.36, maybe uninitialized str
        printf("%d: %s\n", i, str);
        i++;
        curr = curr->next;
    }
    return EXIT_SUCCESS;

}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-25, omitted, human, missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *prev = *head;
    if (pos == 1){
        node *new_node = malloc(sizeof(node));
        // bug 2: id-24, present, approx-0.07, missing strdup
        new_node->item_name = item_name; 
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = *head;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    while (prev != NULL && pos != 2){
        pos--;
        prev = prev->next;
    }
    if (prev == NULL){
        return EXIT_FAILURE;
    }
    node *new_node = malloc(sizeof(node));
    // bug 3: id-24, present, approx-0.13, missing strdup
    new_node->item_name = item_name; 
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = prev->next;
    prev->next = new_node;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-401, omitted, codex, missing check for head == NULL
    node *curr = *head;
    if (pos == 1){
        // bug 2: id-399, omitted, codex, missing free
        // bug 3: id-400, present, codex, missing strdup
        curr->item_name = item_name;
        curr->price = price;
        curr->quantity = quantity;
        return EXIT_SUCCESS;
    }
    while (curr != NULL && pos != 1){
        curr = curr->next;
        pos--;
    }
    if (curr == NULL){
        return EXIT_FAILURE;
    }
    // bug 4: id-399, omitted, approx-0.50, missing free
    // bug 5: id-400, present, approx-0.50, missing strdup
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos) {
    // TODO: Implement this 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-513, omitted, humanf, missing check for head == NULL
    // bug 2: id-514, omitted, humanf, missing check for *head == NULL
    node *temp, *prev;
    if (pos == 1){
        temp = *head;
        *head = temp->next;
        // bug 5: id-511, omitted, humanf, missing free of item
        // bug 6: id-512, omitted, humanf, missing free of item_name
        temp = NULL;
        return EXIT_SUCCESS;
    }else if(pos > 1){
        temp = *head;
        prev = NULL;
        while (pos>1){
            if (temp == NULL){
                return EXIT_FAILURE;
            }
            pos--;
            prev = temp;
            temp = temp->next;
            // bug 3: id-511, omitted, codex, missing free of item
            // bug 4: id-512, omitted, codex, missing free of item_name
        }
        prev->next = temp->next;
        temp = NULL;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-687, omitted, humanf, missing check for head == NULL
    if (pos1 == pos2){
        return EXIT_SUCCESS;
    }
    node *curr1 = *head;
    node *curr2 = *head;
    node *prev1 = NULL;
    node *prev2 = NULL;
    while(curr1 != NULL && curr2 != NULL){
        if (pos1 == 1){
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
        if (pos2 == 1){
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
        pos1--;
        pos2--;
    }
    if (curr1 == NULL || curr2 == NULL){
        return EXIT_FAILURE;
    }
    if (prev1 != NULL){
        prev1->next = curr2;
    }
    else{
        *head = curr2;
    }
    if (prev2 != NULL){
        prev2->next = curr1;
    }
    else{
        *head = curr1;
    }
    node *tmp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = tmp;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) {
    // TODO: Implement this
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: id-612, omitted, human, missing check for pos == NULL
    *pos = 1;
    int i = 1;
    node *curr = head;
    float highest = curr->price;
    while (curr != NULL) {
        if (curr->price > highest) {
            highest = curr->price;
            *pos = i;
        }
        i++;
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total){
    // TODO: Implement this
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node *curr = head;
    float sum = 0;
    while (curr != NULL){
        sum += curr->price * curr->quantity;
        curr = curr->next;
    }
    // bug 1: id-651, omitted, human, missing check for total == NULL
    *total = sum;
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename) {
    // TODO: Implement this {
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    FILE *fp;
    // bug 1: id-808, omitted, humanf, missing check for filename == NULL
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return EXIT_FAILURE;
    }
    node *curr = head;
    while (curr != NULL) {
        // bug 2: id-807, omitted, humanf, missing check for fprintf failure
        // bug 3: id-809, omitted, humanf, missing check for item_name == NULL
        fprintf(fp, "%s,%.2f,%d\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}


int list_load(node **head, char *filename) {
    // TODO: Implement this 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int pos = 1;
    // bug 1: id-898, omitted, human, missing check for head == NULL
    while(*head !=NULL){
        pos++;
        *head = (*head)->next;
    }
    // bug 2: id-899, omitted, human, missing check for filename == NULL
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    // bug 3: id-900, present, human, buffer overflow
    char *item_name = (char *) malloc(sizeof(char)*256);
    float price;
    int quantity;
    // bug 4: id-897, omitted, approx-0.25, fscanf may not initialize all values
    while (fscanf(fp, "%s,%f,%d\n", item_name, &price, &quantity)!= EOF){
        // bug 5: id-895, omitted, approx-0.25, missing check of return status for list_add_item_at_pos
        list_add_item_at_pos(&(*head), item_name, price, quantity, pos);
        pos++;
    }
    // bug 6: id-896, omitted, human, memory leak failing to free item_name
    return EXIT_SUCCESS;
}

int list_deduplicate (node **head) {
    // TODO: Implement this function
    // return EXIT_SUCCESS or EXIT FAILURE when appropriate
    // node *temp, *prev, *curr;
    // prev = NULL;
    // curr = *head;
    // temp = curr->next;
    // while(temp != NULL){
    //     if(strcmp(curr->item_name,temp->item_name) == 0){
    //         curr->quantity = curr->quantity + temp->quantity;
    //         prev->next = temp->next;
    //         free(temp);
    //         temp = prev->next;
    //     }else{
    //         prev = curr;
    //         curr = curr->next;
    //         temp = curr->next;
    //     }
    // }
    return EXIT_SUCCESS;
}

