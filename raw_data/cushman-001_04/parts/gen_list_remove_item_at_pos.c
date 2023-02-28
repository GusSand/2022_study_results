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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    // bug 1: missing check of head == NULL
	if(*head == NULL) {
		fprintf(stderr, "Error: list_remove_item_at_pos cannot remove an item from an empty list.\n");
		return EXIT_FAILURE;
	}
	if(pos == 0) {
		node *head_next = (*head)->next;
        // bug 2: failing to free item_name
		free(*head);
		*head = head_next;
		return EXIT_SUCCESS;
	}
	node *current = *head;
	for(int i = 1; i < pos - 1; i++) {
        // bug 3: missing check for next == NULL
		current = current->next;
	}
    // bug 4: missing check for next == NULL
	node *next = current->next->next;
    // bug 5: failing to free item_name
	free(current->next);
	current->next = next;
	return EXIT_SUCCESS;
}
