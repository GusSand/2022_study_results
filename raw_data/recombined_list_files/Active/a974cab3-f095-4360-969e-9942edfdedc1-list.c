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
    // bug 1: id-230, omitted, human, missing check for str == NULL
    // bug 2: id-231, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-229, omitted, human, missing check for head == NULL
    snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    
    int count = 1;
    while(head != NULL){
        char *str = (char *)malloc(MAX_ITEM_PRINT_LEN);
        // bug 2: id-344, present, humanf, doesn't check return value of list_item_to_string
        list_item_to_string(head, str);
        // bug 3: id-346, omitted, humanf, maybe uninit str
        printf("%d: %s\n", count, str);
        count++;
        head = head->next;
    }
    // bug 1: id-345, omitted, human, memory leak on str
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-85, omitted, approx-0.45, missing check for head == NULL
    // add a new item (name, price, quantity) to the list, such that the added item is the last item
    node *newNode = malloc(sizeof(node));
    // bug 2: id-84, present, approx-0.45, missing strdup
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

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: id-462, omitted, human, missing check for head == NULL
    // bug 2: id-463, omitted, human, missing check for *head == NULL
    if (pos == 0){
        // bug 3: id-460, omitted, human, missing free
        // bug 4: id-461, present, human, missing strdup
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
        // bug 5: id-460, omitted, human, missing free
        // bug 6: id-461, omitted, human, missing strdup
        temp->item_name = item_name;
        temp->price = price;
        temp->quantity = quantity;
        return EXIT_SUCCESS;
    }
}

int list_remove_item_at_pos(node **head, int pos){
    if (pos == 1){
        // bug 1: id-558, omitted, codex, missing check for head == NULL
        // bug 2: id-559, omitted, codex, missing check for *head == NULL
        node *temp = *head;
        *head = (*head)->next;
        free(temp);
        // bug 3: id-557, omitted, codex, missing free of item_name
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
        // bug 4: id-557, omitted, humanf, missing free of item_name
        return EXIT_SUCCESS;
    }
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: id-717, omitted, human, missing check for head == NULL
    // bug 2: id-718, omitted, human, missing check for *head == NULL
    node *temp1 = *head;
    node *temp2 = *head;
    for (int i = 0; i < pos1 - 1; i++){
        // bug 3: id-716, omitted, human, missing check for next == NULL
        temp1 = temp1->next;
    }
    for (int i = 0; i < pos2 - 1; i++){
        // bug 4: id-716, omitted, human, missing check for next == NULL
        temp2 = temp2->next;
    }
    node *temp3 = temp1->next;
    temp1->next = temp2->next;
    temp2->next = temp3;
    // bug 5: id-719, present, human, infinite loop circular
    // bug 6: id-715, omitted, human, memory leak by failing to update head
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) {
    node *temp = head;
    int max = 0;
    int count = 1;
    // bug 1: id-626, omitted, codex, missing check for pos == NULL
    // bug 2: id-627, present, codex, int vs float confusion
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

int list_cost_sum(node *head, float *total){
    float sum = 0;
    while(head != NULL){
        sum = sum + (head->price * head->quantity);
        head = head->next;
    }
    // bug 1: id-662, omitted, human, missing check for total == NULL
    *total = sum;
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // bug 1: id-838, omitted, humanf, missing check for filename == NULL
    FILE *f = fopen(filename, "w");
    if (f == NULL){
        return EXIT_FAILURE;
    }
    while(head != NULL){
        // bug 2: id-837, present, humanf, missing check for fprintf failure
        // bug 3: id-839, omitted, humanf, missing check for item_name == NULL
        fprintf(f, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(f);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // bug 1: id-929, omitted, approx-0.10, missing check for filename == NULL
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        return EXIT_FAILURE;
    }
    char item_name[100];
    float price;
    int quantity;
    int l =0;
    while(!feof(f)){
        // bug 2: id-930, present, human, buffer overflow fixed size buffer
        // bug 3: id-928, present, human, fscanf may not set all values
        // bug 4: id-927, present, human, failure to check fscanf return value
        fscanf(f, "%[^,],%f,%d\n", item_name, &price, &quantity);
        // bug 5: id-927, present, human, missing check of return status for list_add_item_at_pos
        list_add_item_at_pos(head, item_name, price, quantity, l);
        l+=1;
    }
    fclose(f);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    return EXIT_FAILURE;
}


