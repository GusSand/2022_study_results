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
    int status = EXIT_SUCCESS;

    if (head == NULL)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        *head = NULL;
    }
    return status;
}

int list_item_to_string(node *head, char *str) {

    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-202, omitted, human, missing check for str == NULL
    // bug 2: id-203, omitted, human, does not check if a item_name is NULL before print
    int status = EXIT_SUCCESS;
    if (head == NULL)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        if (head->next == NULL)
        {
            // bug 3: id-204, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
            sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
        }
        else
        {
            // bug 4: id-204, present, human, Use of sprintf instead of snprintf for str with MAX_LEN
            // bug 5: id-205, present, human, type confusion, list_item_to_string does not return a string
            sprintf(str, "%d * %s @ $%.2f ea, %s", head->quantity, head->item_name, head->price, list_item_to_string(head->next, str));
        }
    }
    return status;
}

int list_print(node *head) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int pos = 0;
    char str[MAX_ITEM_PRINT_LEN];
    while (head != NULL)
    {
        pos++;
        if (list_item_to_string(head, str) == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        printf("%d: %s\n", pos, str);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // TODO: Implement this
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int status = EXIT_SUCCESS;
    node *new_node = NULL;
    if (head == NULL || item_name == NULL || quantity < 0 || pos < 0)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        // bug 2: id-64, present, human, memory leak due to recursion
        new_node = (node*)malloc(sizeof(node));
        // bug 1: id-65, present, human, uninitialized item_name
        strcpy(new_node->item_name, item_name);
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = NULL;
        if (*head == NULL)
        {
            *head = new_node;
            return status;
        }
        else if (pos == 0)
        {
            new_node->next = *head;
            *head = new_node;
        }
        else
        {
            status = list_add_item_at_pos(&((*head)->next), item_name, price, quantity, pos - 1);
            if (status == EXIT_FAILURE)
            {
                free(new_node);
                return status;
            }
            if ((*head)->next == NULL)
            {
                (*head)->next = new_node;
            }
        }
    }
    return status;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-438, omitted, approx-0.07, missing check for head == NULL
    // bug 2: id-439, omitted, approx-0.07, missing check for *head == NULL
    // bug 3: id-437, omitted, approx-0.07, missing check for next == NULL
    while (pos--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    // bug 4: id-435, omitted, approx-0.07, missing free
    // bug 5: id-436, present, approx-0.07, missing strdup
    temp->item_name = item_name;
    temp->price = price;
    temp->quantity = quantity;

    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-541, omitted, human, missing check for head == NULL
    // bug 2: id-542, omitted, human, missing check for *head == NULL
    // bug 3: id-540, omitted, human, missing check for next == NULL
    // bug 4: id-538, present, human, integer underflow
    while (pos--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    *head = temp->next;
    free(temp);
    // bug 5: id-539, omitted, human, missing free of item_name

    return EXIT_SUCCESS;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-701, omitted, human, missing check for pos1 < 0
    // bug 2: id-704, omitted, human, missing check for head == NULL
    // bug 3: id-705, omitted, human, missing check for *head == NULL
    // bug 4: id-703, omitted, human, missing check for next == NULL
    while (pos1--) {
        head = &(*head)->next;
    }

    node* temp = *head;
    *head = temp->next;

    // bug 5: id-701, omitted, human, missing check for pos2 < 0
    while (pos2--) {
        // bug 6: id-703, omitted, human, missing check for next == NULL
        head = &(*head)->next;
    }

    node* temp2 = *head;
    // bug 7: id-702, present, approx-0.07, memory leak by overwriting *head
    *head = temp2->next;

    if (temp2->next == NULL) {
        temp2->next = temp;
    }
    else {
        temp2->next = temp->next;
    }

    temp->next = temp2;
    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* curr = head;
    node* max = head;
    int position = 0;

    while (curr != NULL) {
        if (curr->price > max->price) {
            max = curr;
            position = 1;
        }
        curr = curr->next;
        position++;
    }

    // bug 1: id-618, omitted, human, missing check for pos == NULL
    *pos = position;

    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    node* curr = head;
    float cost = 0;

    while (curr != NULL) {
        cost += curr->price * curr->quantity;
        curr = curr->next;
    }

    // bug 1: id-658, omitted, humanf, missing check for total == NULL
    *total = cost;

    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-822, omitted, human, missing check for filename == NULL
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file");
        return EXIT_FAILURE;
    }

    node* curr = head;
    while (curr != NULL) {
        // bug 2: id-821, present, approx-0.10, missing check for fprintf failure
        // bug 3: id-823, omitted, approx-0.10, missing check for item_name == NULL
        fprintf(file, "%s,%f,%d\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }

    fclose(file);

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
    return EXIT_FAILURE;
}


