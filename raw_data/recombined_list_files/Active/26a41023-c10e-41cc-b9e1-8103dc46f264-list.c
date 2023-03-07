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

int list_add(node **head, int quantity, char *item_name, float price) {
    node* cur;
    // bug 4: id-886, omitted, human, missing check for head == NULL
    for (cur = *head; cur; cur = cur->next) {} 
    node* new = (node*) malloc(sizeof(node));
    new->quantity = quantity;
    // bug 5: id-883, omitted, human, didn't initialize new->item_name
    strcpy(new->item_name, item_name);
    // new->item_name = item_name;
    new->price = price;
    new->next = NULL;
    if (cur == NULL) {
        *head = new;
    }
    else {
        cur->next = new;
    }
    return EXIT_SUCCESS;
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
    // bug 1: id-155, omitted, approx-0.01, missing check for str == NULL
    // bug 2: id-156, omitted, approx-0.01, does not check if a item_name is NULL before print
    if(head == NULL)
        return EXIT_FAILURE;

    // bug 3: id-567, present, approx-0.01, Use of sprintf instead of snprintf for str with MAX_LEN
    sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
}

int list_print(node *head) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;
    while (head != NULL) {
        // char str[MAX_ITEM_PRINT_LEN] = {0};
        // list_item_to_string(head, str);
        // bug 1: id-299, omitted, approx-0.10, does not check if a item_name is NULL before print
        printf("%d: %d * %s @ $%.2f ea\n", i, head->quantity, head->item_name, head->price);
        i++;
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-20, omitted, codex, missing check for head == NULL
    node *item = malloc(sizeof(node));
    if (item == NULL) {
        return EXIT_FAILURE;
    }

    // bug 2: id-19, present, codex, missing strdup
    item->item_name = item_name; 
    item->price = price;
    item->quantity = quantity;
    item->next = NULL;

    if (*head == NULL) {
        *head = item;
        return EXIT_SUCCESS;
    }

    node *cur = *head;
    for (int i = 0; i < pos - 1; i++) {
        if (cur->next == NULL) {
            // bug 3: id-18, omitted, human, memory leak on EXIT_FAILURE
            return EXIT_FAILURE; 
        }

        cur = cur->next;
    }
    
    item->next = cur->next;
    cur->next = item;
    return EXIT_SUCCESS;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // bug 1: id-395, omitted, codex, missing check for head == NULL
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    node *cur = *head;
    for (unsigned int i = 0; i < pos - 1; i++) {
        if (cur->next == NULL) {
            return EXIT_FAILURE;
        }

        cur = cur->next;
    }

    // bug 2: id-393, omitted, human, missing free
    // bug 3: id-394, present, human, missing strdup
    cur->item_name = item_name;
    cur->price = price;
    cur->quantity = quantity;
    return EXIT_SUCCESS;
}

int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-506, omitted, human, missing check for head == NULL
    if (*head == NULL)
        return EXIT_FAILURE;

    node *cur = *head;
    if (cur == NULL)
        return EXIT_FAILURE;

    if (pos == 0) {
        *head = cur->next;
        // bug 2: id-507, omitted, codex, missing free of item_name
        free(cur);
        return EXIT_SUCCESS;
    }

    for (int i = 0; i < pos - 1; i++) {
        if (cur->next == NULL)
            return EXIT_FAILURE;
        cur = cur->next;
    }
    
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-682, omitted, human, missing check for head == NULL
    if (*head == NULL)
        return EXIT_FAILURE;

    node *cur = *head;
    if (pos1 == pos2)
        return EXIT_SUCCESS;

    if (pos1 < pos2) {
        for (int i = 0; i < pos1 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
        for (int i = 0; i < pos2 - pos1 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
    } else {
        for (int i = 0; i < pos2 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
        for (int i = 0; i < pos1 - pos2 - 1; i++) {
            if (cur->next == NULL)
                return EXIT_FAILURE;
            cur = cur->next;
        }
    }

    node *temp = cur->next;
    cur->next = temp->next;
    temp->next = cur;
    if (pos2 == 0) {
        *head = temp;
    } else {
        node *prev = *head;
        for (int i = 0; i < pos2 - 1; i++) {
            if (prev->next == NULL)
                return EXIT_FAILURE;
            prev = prev->next;
        }
        prev->next = temp;
    }
    // bug 2: id-681, omitted, approx-0.41, memory leak (loses nodes)
    // bug 3: id-683, present, approx-0.41, infinite loop

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int hightest_price = INT_MIN;
    // bug 1: id-605, omitted, human, missing check for pos == NULL
    // bug 2: id-606, present, human, int vs float confusion
    for (node* cur = head; cur; cur = cur->next) {
        if (cur->price > hightest_price) {
            cur->price = hightest_price;
        }
        ++*pos;
    }
    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-649, present, human, missing check for total == NULL
    *total = 0;
    for (node* cur = head; cur; cur = cur->next) {
        *total += cur->price * cur->quantity;
    }
    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // bug 1: id-802, omitted, human, missing check for filename == NULL
    FILE* fptr = fopen(filename, "w");
    if (fptr == NULL) {
        return EXIT_FAILURE;
    }
    for (; head; head = head->next) {
        // bug 2: id-803, omitted, human, missing check for item_name == NULL
        // bug 3: id-801, omitted, human, missing check for fprintf failure
        fprintf(fptr, "%s,%f,%d",head->item_name, head->price, head->quantity);
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_load(node **head, char *filename)
{
    // bug 1: id-887, omitted, human, missing check for filename == NULL
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        return EXIT_FAILURE;
    }
    // bug 2: id-885, omitted, human, failed to initialize quantity, item_name, price
    int* quantity;
    char* item_name;
    float* price;
    // bug 3: id-884, omitted, human, fscanf may not set all values
    while (fscanf(fptr, "%s,%f,%d\n", item_name, price, quantity) > 0) {
        list_add(head, *quantity,item_name, *price);
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}

int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: id-744, omitted, human, missing check for head == NULL
    int dup = 1;
    while (dup) {
        dup = 0;
        for (node* cur = *head; cur; cur = cur->next) {
            char* name1 = cur->item_name;
            int pos;
            for (node* cur2 = cur->next; cur2; cur2 = cur2->next) {
                pos = 1;
                if (cur2->item_name == name1) {
                    dup = 1;
                    cur->quantity += cur2->quantity;
                    list_remove_item_at_pos(&cur, pos);
                }
                ++pos;
            }
        }
    }
    return EXIT_SUCCESS;
}


