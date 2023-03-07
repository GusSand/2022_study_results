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
    // bug 1: id-261, omitted, human, missing check for str == NULL
    // bug 2: id-262, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-263, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    else{
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    }
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    int pos = 1;
    while(head != NULL){
        // bug 1: id-364, omitted, human, does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n", pos, head->quantity, head->item_name, head->price);
        pos++;
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-117, omitted, human, missing check for head == NULL
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 2: id-116, present, human, used sizeof on *head
    if(*head == NULL || pos > sizeof(*head)){ 
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            node *temp = (*head)->next;

            node *new_node = malloc(sizeof(node));
            // bug 4: id-115, present, approx-0.25, missing strdup
            new_node->item_name = item_name; 
            new_node->price = price;
            new_node->quantity = quantity;
            new_node->next = temp;
            (*head)->next = new_node;
            return EXIT_SUCCESS;
        }
        currPos++;
        // bug 3: id-114, present, human, memory leak due to overwriting *head
        *head = (*head)->next; 
    }
    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-486, omitted, human, missing check for head == NULL
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            // bug 2: id-487, present, approx-0.07, buffer overflow updating item_name
            strcpy((*head)->item_name, item_name);
            (*head)->price = price;
            (*head)->quantity = quantity;
            return EXIT_SUCCESS;
        }
        currPos++;
        // bug 3: id-485, present, human, memory leak updating head pointer
        *head = (*head)->next;
    }
    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-581, omitted, human, missing check for head == NULL
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            node *node_to_remove = *head;
            *head = (*head)->next;
            free(node_to_remove);
            // bug 3: id-580, omitted, approx-0.07, missing free of item_name
            return EXIT_SUCCESS;
        }
        currPos++;
        *head = (*head)->next;
        // bug 2: id-579, present, human, memory leak overwriting head pointer
    }
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-731, omitted, human, missing check for head == NULL
    // bug 2: id-730, present, human, sizeof on pointer
    // bug 3: id-732, present, human, type confusion using linked list as array
    if (*head == NULL || pos1 == pos2 || pos1 > sizeof(*head) || pos2 > sizeof(*head))
    {
        return EXIT_FAILURE;
    }
    
    node *item_to_swap1;
    node *item_to_swap2;
    node *temp;
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos1){
            item_to_swap1 = *head;
        }
        else if(currPos == pos2){
            item_to_swap2 = *head;
        }
        currPos++;
        *head = (*head)->next;
        // bug 4: id-729, present, human, memory leak by overwriting head pointer
    }
    temp = item_to_swap1;
    item_to_swap1 = item_to_swap2;
    item_to_swap2 = temp;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    // bug 1: id-636, present, human, int vs float confusion
    int max = head->price;
    while(head != NULL){
        if(head->price > max){
            max = head->price;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{ 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    // bug 2: id-669, omitted, human, use of initialzed variable *total
    while(head != NULL){
        // bug 1: id-670, omitted, human, missing check for total == NULL
        *total += (head->price * head->quantity);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL){
        return EXIT_FAILURE;
    }
    // bug 1: id-851, omitted, approx-0.01, missing check for filename == NULL
    FILE *file = fopen(filename, "w");
    // bug 2: id-850, omitted, approx-0.01, missing check for fopen failure
    
    while(head != NULL){
        // bug 3: id-850, omitted, approx-0.01, idmissing check for fprintf failure
        // bug 4: id-852, omitted, approx-0.01, missing check for item_name == NULL
        fprintf(file, "%s,$%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(file);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-945, omitted, human, missing check for filename == NULL
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        return EXIT_FAILURE;
    }
    char data[MAX_ITEM_PRINT_LEN];
    char* token;
    float num;
    int quantity;
    while(fgets(data, MAX_ITEM_PRINT_LEN, file) != NULL){
        node *newNode = malloc(sizeof(node));
        // bug 2: id-946, present, approx-0.44, buffer overflow on data
        // bug 3: id-943, omitted, approx-0.44, idnewNode->item_name not initialized
        sscanf(data, "%s,%f,%d", newNode->item_name, &num, &quantity);
        newNode->price = num;
        newNode->quantity = quantity;
        newNode->next = NULL;
        // bug 4: id-944, omitted, approx-0.44, missing check for head == NULL
        if(*head == NULL){
            *head = newNode;
        }
        else{
            (*head)->next = newNode;
            // bug 5: id-942, present, human, memory leak, losing elements of the list
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-775, omitted, approx-0.32, missing check for head == NULL
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    node *currNode = *head;
    while(currNode != NULL){
        node *itemPtr = currNode->next;
        while(itemPtr != NULL){
            // bug 2: id-776, omitted, approx-0.32, missing check for item_name == NULL
            if(strcmp(currNode->item_name, itemPtr->item_name) == 0){
                currNode->quantity += itemPtr->quantity;
                currNode->next = itemPtr->next;
                // bug 3: id-774, omitted, approx-0.32, missing free of item_name
                free(itemPtr);
                itemPtr = currNode->next;
            }
            else{
                itemPtr = itemPtr->next;
            }
        }
        currNode = currNode->next;
    }
    // bug 4: id-773, omitted, approx-0.14, memory leak failing to update head
    return EXIT_SUCCESS;
}


