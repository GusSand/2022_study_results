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
    // bug 1: id-240, omitted, human, missing check for str == NULL
    // bug 2: id-241, omitted, human, does not check if a item_name is NULL before print
    // bug 3: id-242, omitted, human, Use of sprintf instead of snprintf for str with MAX_LEN
    if (head == NULL) {
        return EXIT_SUCCESS;
    }

    sprintf(str, "%d * %s @ %.2f ea", head->quantity, head->item_name, head->price);

    return EXIT_SUCCESS;
}

int list_print(node *head) {
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    unsigned int pos = 1;
    while(head != NULL) {
        // bug 1: id-352, omitted, human, does not check if a item_name is NULL before print
        printf("%d: %d * %s @ %.2f ea\n", pos, head->quantity, head->item_name, head->price);
        head = head->next;
        pos++;
    }

    return EXIT_SUCCESS;
}

int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    // bug 1: id-99, omitted, human, missing check for head == NULL
    unsigned int i = 1;
    node *prev = NULL;
    node *curr = *head;

    if(pos == 0)
        return EXIT_FAILURE;
    

    while(curr != NULL) {
        if(i == pos) {
            node newItem;
            // bug 2: id-98, present, human, missing strdup
            newItem.item_name = item_name; 
            newItem.price = price;
            newItem.quantity = quantity;
            newItem.next = curr;

            if(prev == NULL) {
                // bug 3: id-100, present, human, returning a stack variable
                *head = &newItem; 
            } else {
                // bug 4: id-100, present, human, returning a stack variable
                prev->next = &newItem; 
            }

            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }

    return EXIT_FAILURE;
}

int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    unsigned int i = 1;
    node *prev = NULL;
    // bug 1: id-466, omitted, codex, missing check for head == NULL
    node *curr = *head;

    if(pos == 0)
        return EXIT_FAILURE;

    while(curr != NULL) {
        if(i == pos) {
            // bug 2: id-464, omitted, codex, missing free
            // bug 3: id-465, present, codex, missing strdup
            curr->item_name = item_name;
            curr->price = price;
            curr->quantity = quantity;

            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }

    return EXIT_FAILURE;
}

int list_remove_item_at_pos(node **head, int pos) {
    int i = 1;
    // bug 1: id-562, omitted, human, missing check for head == NULL
    node *prev = NULL;
    node *curr = *head;

    if(pos == 0)
        return EXIT_FAILURE;

    while(curr != NULL) {
        if(i == pos) {
            // If prev is NULL, we are removing the head
            if(prev == NULL) {
                *head = curr->next;
                // bug 2: id-561, omitted, codex, missing free of item
                // bug 3: id-560, omitted, codex, missing free of item_name
            } else {
                prev->next = curr->next;
                // bug 4: id-561, omitted, codex, missing free of item
                // bug 5: id-560, omitted, codex, missing free of item_name
            }

            return EXIT_SUCCESS;
        }

        prev = curr;
        curr = curr->next;
        i++;
    }
    
    return EXIT_FAILURE;
}

int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: id-720, omitted, human, missing check for head == NULL
    node *prev1 = NULL;
    node *curr1 = *head;

    int i = 1;
    while(curr1 != NULL) {
        if(i == pos1) {
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
    }

    node *prev2 = NULL;
    node *curr2 = *head;

    i = 1;
    while(curr2 != NULL) {
        if(i == pos2) {
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if(prev1 == NULL) {
        *head = curr2;
    } else {
        prev1->next = curr2;
    }

    if(prev2 == NULL) {
        *head = curr1;
    } else {
        prev2->next = curr1;
    }

    // bug 2: id-721, omitted, codex, missing/wrong check for cur == NULL
    if(curr1->next == curr2) {
        curr1->next = curr2->next;
        curr2->next = curr1;
    // bug 3: id-721, omitted, codex, missing/wrong check for cur == NULL
    } else if(curr2->next == curr1) {
        curr2->next = curr1->next;
        curr1->next = curr2;
    }

    return EXIT_SUCCESS;
}

int list_find_highest_price_item_position(node *head, int *pos) 
{
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    // bug 1: id-628, omitted, codex, missing check for pos == NULL
    // bug 2: id-629, prsent, codex, int vs float confusion
    int highestPrice = 0;
    int highestPricePos = 0;
    unsigned int i = 1;

    while(head != NULL) {
        if(head->price > highestPrice) {
            highestPrice = head->price;
            highestPricePos = i;
        }
        head = head->next;
        i++;
    }

    *pos = highestPricePos;

    return EXIT_SUCCESS;
}

int list_cost_sum(node *head, float *total)
{
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    // bug 1: id-663, omitted, approx-0.46, missing check for total == NULL
    *total = 0;
    while(head != NULL) {
        *total += (head->quantity * head->price);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int list_save(node *head, char *filename)
{
    // bug 1: id-842, omitted, human, missing check for filename == NULL
    FILE *f = fopen(filename, "w");
    if(f == NULL) {
        return EXIT_FAILURE;
    }

    while(head != NULL) {
        // bug 2: id-840, present, human, missing check for fprintf failure
        // bug 3: id-843, omitted, human, missing check for item_name == NULL
        fprintf(f, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);

        head = head->next;
    }
    // bug 4: id-841, omitted, human, missing fclose
}

int list_load(node **head, char *filename)
{
    // bug 1: id-931, omitted, human, missing check for filename == NULL
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        return EXIT_FAILURE;
    }
    // bug 2: id-932, omitted, human, missing return statement
}

int list_deduplicate(node **head) 
{
    return EXIT_SUCCESS;
}


