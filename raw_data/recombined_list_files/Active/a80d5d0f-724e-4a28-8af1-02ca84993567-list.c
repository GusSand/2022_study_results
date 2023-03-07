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
    // bug 1: id-226, omitted, approx-0.20, missing check for str == NULL
    // bug 2: id-227, omitted, approx-0.20, does not check if a item_name is NULL before print
    // bug 3: id-228, present, approx-0.20, Use of sprintf instead of snprintf for str with MAX_LEN
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    }
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        int pos = 1;
        while (cur != NULL) {
            // bug 1: id-343, present, codex, type confusion, list_item_to_string returns int not char *
            // bug 2: id-342, present, human, using cur->item_name instead of their own buffer, cur->item_name may be too short
            printf("%d: %s\n", pos, list_item_to_string(cur, cur->item_name));
            cur = cur->next;
            pos++;
        }
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-83, omitted, human, missing check for head == NULL
    if (pos<1) {
        return EXIT_FAILURE;
    }
    if (*head == NULL) {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) {
            return EXIT_FAILURE;
        }
        // bug 2: id-82, present, approx-0.45, missing strdup
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = NULL;
        *head = new_node;
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    node *prev = NULL;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        prev = curr;
        curr = curr->next;
    }
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return EXIT_FAILURE;
    }
    // bug 3: id-82, present, codex, missing strdup
    new_node->item_name = item_name;
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = curr;
    if (curr == *head) {
        *head = new_node;
    } else {
        prev->next = new_node;
    }
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    if (pos<1) {
        return EXIT_FAILURE;
    }
    // bug 1: id-459, omitted, humanf, missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = *head;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    // bug 2: id-457, omitted, humanf, missing free
    // bug 3: id-458, present, humanf, missing strdup
    curr->item_name = item_name;
    curr->price = price;
    curr->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    if (pos<1) {
        return EXIT_FAILURE;
    }
    // bug 1: id-556, omitted, codex, missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos == 1) {
        node *curr = *head;
        *head = curr->next;
        // bug 2: id-555, omitted, human, missing free of item_name
        free(curr);
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    node *prev = NULL;
    for (unsigned int i=1; i<pos; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    free(curr);
    // bug 3: id-555, omitted, codex, missing free of item_name
    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (pos1 < 1 || pos2 < 1) {
        return EXIT_FAILURE;
    }
    // bug 1: id-714, omitted, human, missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    node *curr = *head;
    for (unsigned int i=1; i<pos1; i++) {
        if (curr == NULL) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    list_update_item_at_pos(head, curr->item_name, curr->price, curr->quantity, pos2);
    node *curr2 = *head;
    

    for (unsigned int i=1; i<pos2; i++) {
        if (curr2 == NULL) {
            return EXIT_FAILURE;
        }
        curr2 = curr2->next;
    }
    list_update_item_at_pos(head, curr2->item_name, curr2->price, curr2->quantity, pos1);
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur = head;
        int curr_pos  = 1 ; 
        // bug 1: id-624, present, humanf, int vs float confusion
        int max = -1; 
        while (cur != NULL) {
            if (cur->price > max) {
                max = cur->price; 
                // bug 2: id-625, present, human, int* vs int confusion
                pos = curr_pos; 
                }
            cur = cur->next;
            curr_pos++;
        }
    }
    return EXIT_SUCCESS;
    
}

int list_cost_sum(node *head, float *total){
    
        return EXIT_SUCCESS; 

}

int list_save(node *head, char *filename)
{
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    return EXIT_SUCCESS; 
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate 

    return EXIT_SUCCESS;
}


