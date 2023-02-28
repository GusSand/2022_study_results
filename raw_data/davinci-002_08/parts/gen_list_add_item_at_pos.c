#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
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

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS

#include "reflist.h"
// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 2 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    node *curr = *head;
    node *prev = NULL;
    int i = 1;

    if (head == NULL || item_name == NULL) {
        return EXIT_FAILURE;
    }

    if (pos == 0) {
        node *new = malloc(sizeof(node));
        new->item_name = malloc(strlen(item_name) * sizeof(char) + 1);
        memset(new->item_name, 0, strlen(item_name) * sizeof(char) + 1);
        strcpy(new->item_name, item_name);
        new->price = price;
        new->quantity = quantity;
        new->next = *head;
        *head = new;
        return EXIT_SUCCESS;
    }

    while (curr != NULL) {
        if (i == pos) {
            node *new = malloc(sizeof(node));
            new->item_name = malloc(strlen(item_name) * sizeof(char) + 1);
            memset(new->item_name, 0, strlen(item_name) * sizeof(char) + 1);
            strcpy(new->item_name, item_name);
            new->price = price;
            new->quantity = quantity;
            new->next = curr;
            if (prev != NULL) {
                prev->next = new;
            }
            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }
    return EXIT_FAILURE;
}
