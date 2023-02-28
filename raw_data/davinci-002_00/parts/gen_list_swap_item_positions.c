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
    if (*head == NULL || pos1 == 0 || pos2 == 0) {
        return EXIT_FAILURE;
    }
    int cur_pos = 1;
    node *cur = *head;
    while (cur->next && cur_pos < pos1-1) {
        cur = cur->next;
        cur_pos++;
    }
    if (cur_pos == pos1-1) {
        node *temp = cur->next;
        cur->next = cur->next->next;
        cur = cur->next;
        cur_pos++;
        while (cur->next && cur_pos < pos2-1) {
            cur = cur->next;
            cur_pos++;
        }
        if (cur_pos == pos2-1) {
            node *temp2 = cur->next;
            cur->next = temp;
            temp->next = temp2->next;
            free(temp2->item_name);
            free(temp2);
        } else {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
