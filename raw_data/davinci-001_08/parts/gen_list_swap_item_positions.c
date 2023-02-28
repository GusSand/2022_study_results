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
    int result = EXIT_SUCCESS;
    node *pos1_node = NULL;
    node *pos2_node = NULL;
    node *prev_to_pos1 = NULL;
    node *prev_to_pos2 = NULL;
    int i = 0;

    if (pos1 == pos2) {
        return result;
    }

    if (pos1 == 0) {
        pos1_node = *head;
    } else {
        prev_to_pos1 = *head;

        while (i < pos1) {
            prev_to_pos1 = pos1_node;
            pos1_node = pos1_node->next;
            i++;
        }
    }

    if (pos2 == 0) {
        pos2_node = *head;
    } else {
        prev_to_pos2 = *head;

        while (i < pos2) {
            prev_to_pos2 = pos2_node;
            pos2_node = pos2_node->next;
            i++;
        }
    }

    if (pos1_node == NULL || pos2_node == NULL) {
        result = EXIT_FAILURE;
    } else {
        if (pos1_node == *head) {
            *head = pos2_node;
        } else {
            prev_to_pos1->next = pos2_node;
        }

        if (pos2_node == *head) {
            *head = pos1_node;
        } else {
            prev_to_pos2->next = pos1_node;
        }

        node *temp = pos1_node->next;
        pos1_node->next = pos2_node->next;
        pos2_node->next = temp;
    }

    return result;
}
