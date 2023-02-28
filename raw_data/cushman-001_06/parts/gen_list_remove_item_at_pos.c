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
	// If pos is 0, return EXIT_FAILURE
	if (pos == 0) {
		return EXIT_FAILURE;
	}

	// If pos is 1, remove the head
	if (pos == 1) {
		node *temp = *head;
		*head = (*head)->next;
		free(temp->item_name);
		free(temp);
		return EXIT_SUCCESS;
	}

	// If pos is greater than 1, find the node at pos - 1
	int i;
	node *current = *head;
	for (i = 1; i < pos - 1; i++) {
		current = current->next;
		if (current == NULL) {
			return EXIT_FAILURE;
		}
	}

	// Remove the node
	node *temp = current->next;
	current->next = temp->next;
	free(temp->item_name);
	free(temp);
	return EXIT_SUCCESS;
}
