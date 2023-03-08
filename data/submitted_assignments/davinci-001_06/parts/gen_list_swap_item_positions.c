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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        node *cur1 = *head;
        node *cur2 = *head;
        unsigned int k1 = 0;
        unsigned int k2 = 0;
        while (cur1 != NULL) {
            if (k1 == pos1) {
                break;
            } else {
                k1++;
                cur1 = cur1->next;
            }
        }
        while (cur2 != NULL) {
            if (k2 == pos2) {
                break;
            } else {
                k2++;
                cur2 = cur2->next;
            }
        }
        if (cur1 == NULL || cur2 == NULL) {
            return EXIT_FAILURE;
        } else {
            cur1->item_name = malloc(strlen(cur2->item_name) + 1);
            if (cur1->item_name == NULL) {
                return EXIT_FAILURE;
            }
            strcpy(cur1->item_name, cur2->item_name);
            cur1->price = cur2->price;
            cur1->quantity = cur2->quantity;
            cur2->item_name = malloc(strlen(cur1->item_name) + 1);
            if (cur2->item_name == NULL) {
                return EXIT_FAILURE;
            }
            strcpy(cur2->item_name, cur1->item_name);
            cur2->price = cur1->price;
            cur2->quantity = cur1->quantity;
            return EXIT_SUCCESS;
        }
    }
}
