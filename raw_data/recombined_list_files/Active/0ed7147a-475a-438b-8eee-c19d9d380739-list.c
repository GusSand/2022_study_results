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
    if (!head) return EXIT_FAILURE;
    if (!str) return EXIT_FAILURE;
    // bug 1: id-145, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
    // bug 2: id-144, omitted, human, does not check if item_name is NULL before print
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL)
        return EXIT_FAILURE;
    struct _node *curr = head;
    int pos = 0;
    while (curr != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        // bug 1: id-295, present, human, doesn't check return value of list_item_to_string
        list_item_to_string(curr, item_str);
        // bug 2: id-296, omitted, human, item_str may be uninitialized
        printf("%d: %s\n", pos++, item_str);
        curr = curr->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: id-6, omitted, codex, missing check for head == NULL

    if (pos == 0) {
        node *temp = (node *) malloc(sizeof(node));
        temp->next = (*head);
        (*head) = temp;
        temp->quantity = quantity;
        // bug 2: id-5, omitted, codex, doesn't initialize item_name
        strncpy(temp->item_name, item_name, MAX_ITEM_PRINT_LEN); 
        temp->price = price;
        return EXIT_SUCCESS;
    }

    struct _node *curr = *head;
    struct _node *prev = NULL;
    int i = 0;

    while (curr != NULL && i < pos) {
        prev = curr;
        curr = curr->next;
        i++;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    else {
        node *temp = (node *) malloc(sizeof(node));
        temp->next = curr;
        prev->next = temp;
        temp->quantity = quantity;
        // bug 3: id-5, omitted, codex, doesn't initialize item_name
        strncpy(temp->item_name, item_name, MAX_ITEM_PRINT_LEN); 
        temp->price = price;
        return EXIT_SUCCESS;
    }
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-386, omitted, human, missing check for head == NULL
    // bug 2: id-387, omitted, human, missing check for *head == NULL
    if (pos == 0) {
        (*head)->quantity = quantity;
        // bug 3: id-388, omitted, human, out of bounds write if new item_name is longer than old item_name
        // bug 4: id-385, omitted, human, possible improper NULL termination
        strncpy((*head)->item_name, item_name, MAX_ITEM_PRINT_LEN);
        (*head)->price = price;
        return EXIT_SUCCESS;
    }

    struct _node *curr = *head;
    int i = 0;

    while (curr != NULL && i < pos) {
        curr = curr->next;
        i++;
    }

    if (curr == NULL) {
        return EXIT_FAILURE;
    }
    else {
        curr->quantity = quantity;
        // bug 5: id-388, omitted, human, out of bounds write if new item_name is longer than old item_name
        // bug 6: id-385, omitted, human, possible improper NULL termination
        strncpy(curr->item_name, item_name, MAX_ITEM_PRINT_LEN);
        curr->price = price;
        return EXIT_SUCCESS;
    }
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-600, omitted, human, missing check for pos == NULL
    // bug 2: id-601, present, human, int vs float confusion
    if (head == NULL) return EXIT_FAILURE;
    int i = 0, max_i = 0, max_price = 0;
    while (head != NULL) {
        if (head->price > max_price) {
            max_i = i;
            max_price = head->price;
        }
        head = head->next;
        i++;
    }
    *pos = max_i;
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) return EXIT_FAILURE;
    float sum = 0;
    while (head != NULL) {
        sum += head->price * head->quantity;
        head = head->next;
    }
    // bug 1: id-647, omitted, approx-0.33, missing check for total == NULL
    *total = sum;
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


