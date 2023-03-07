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

// Auxiliary functions

node* getIndex(node* curr, int index) {
    if (curr == NULL)
        return 0;
    else if (index > 2) {
        return getIndex(curr->next, index - 1);
    } else {
        return curr;
    }
}

// Main API functions

int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-152, omitted, unrecorded, missing check for str == NULL
    // bug 2: id-153, omitted, unrecorded, does not check if a item_name is NULL before print
    // bug 3: id-154, present, unrecorded, Use of sprintf instead of snprintf for str with MAX_LEN
    if (head == NULL)
        return EXIT_FAILURE;
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);

    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-17, omitted, unrecorded, missing check for head == NULL

    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (*head == NULL) {
        *head = malloc(sizeof(node));
        // bug 2: id-16, omitted, unrecorded, missing strdup
        (*head)->item_name = item_name;
        (*head)->price = price;
        (*head)->quantity = quantity;
        (*head)->next = NULL;
        return EXIT_SUCCESS;
    }
    // if (pos == 0) {
    //     node* new_node = malloc(sizeof(node));
    //     new_node->item_name = item_name;
    //     new_node->price = price;
    //     new_node->quantity = quantity;
    //     new_node->next = *head;
    //     *head = new_node;
    //     return EXIT_SUCCESS;
    // }
    node* curr = *head;
    curr = getIndex(curr, pos);
    if (curr == NULL)
        return EXIT_FAILURE;
    node* newNode = malloc(sizeof(struct node));
    // bug 3: id-17, omitted, unrecorded, missing strdup
    newNode->item_name = item_name;
    newNode->price = price;
    newNode->quantity = quantity;
    if (pos == 1) {
        newNode->next = *head;
        *head = newNode;
    } else {
        newNode->next = curr->next;
        curr->next = newNode;
    }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: id-392, omitted, unrecorded, missing check for head == NULL
    node* curr = *head;
    curr = getIndex(curr, pos);
    if (curr == NULL)
        return EXIT_FAILURE;
    // bug 2: id-390, omitted, unrecorded, missing free
    // bug 3: id-391, present, unrecorded, missing strdup
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{   
    // bug 1: id-504, omitted, unrecorded, missing check for head == NULL
    node* curr = *head;
    curr = getIndex(curr, pos);
    if (curr == NULL)
        return EXIT_FAILURE;
    if (pos == 1) {
        *head = curr->next;
        // bug 3: id-503, omitted, unrecorded, missing free of item_name
        free(curr);
    } else {
        node* toDelete = curr->next;
        // bug 2: id-505, omitted, unrecorded, print item_name without NULL check
        printf("%s\n", toDelete->item_name);
        curr->next = toDelete->next;
        // bug 4: id-503, omitted, unrecorded, missing free of item_name
        free(toDelete);
    }
    
    
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: id-680, omitted, unrecorded, missing check for head == NULL
    node* curr1 = getIndex(*head, pos1);
    node* curr2 = getIndex(*head, pos2);
    node* temp = NULL;
    if (pos1 == pos2)
        return EXIT_SUCCESS;
    temp = *head;
    if (pos1 == 1) {
        temp = *head;
        (*head) = curr2->next;
        curr2->next = temp;
        // bug 2: id-679, omitted, unrecorded, missing check for next == NULL
        temp = curr2->next->next;
        curr2->next->next = (*head)->next;
        (*head)->next = temp;
    }
    else if (pos2 == 1) {
        temp = *head;
        (*head) = curr1->next;
        curr1->next = temp;
        // bug 3: id-679, omitted, unrecorded, missing check for next == NULL
        temp = curr1->next->next;
        curr1->next->next = (*head)->next;
        (*head)->next = temp;
    } else {
        temp = curr1->next;
        curr1->next = curr2->next;
        curr2->next = temp;
        // bug 4: id-679, omitted, unrecorded, missing check for next == NULL
        temp = curr1->next->next;
        curr1->next->next = curr2->next->next;
        curr2->next->next = temp;
    }

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    float max = head->price;
    int curr = 1;
    // bug 1: id-604, omitted, unrecorded, missing check for pos == NULL
    *pos = 1;
    while (head != NULL) {
        if(head->price > max) {
            *pos = curr;
            max = head->price;
        }
        ++curr;
        head = head->next;
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
    FILE* ptr;
    // bug 1: id-799, omitted, unrecorded, missing check for filename == NULL
    ptr = fopen(filename, "w");
    char str[MAX_ITEM_PRINT_LEN];
    if (ptr == NULL) {
        return EXIT_FAILURE;
    }
    while (head != NULL) {
        list_item_to_string(head, str);
        // bug 2: id-798, present, unrecorded, missing check for fprintf failure
        // bug 3: id-800, omitted, unrecorded, missing check for item_name == NULL
        fprintf(ptr, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(ptr);
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


