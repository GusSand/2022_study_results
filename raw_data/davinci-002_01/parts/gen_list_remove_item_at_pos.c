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
	if (pos < 1) {
		return EXIT_FAILURE;
	}

	if (*head == NULL) {
		return EXIT_FAILURE;
	}
	if (pos == 1) {
		node *removed_node = *head;
		*head = (*head)->next;
		free(removed_node->item_name);
		free(removed_node);
		return EXIT_SUCCESS;
	}
	unsigned int current_pos = 1;
	node *current = *head;
	while (current->next != NULL && current_pos < pos - 1) {
		current = current->next;
		current_pos += 1;
	}
	if (current_pos != pos - 1) {
		return EXIT_FAILURE;
	}
	node *removed_node = current->next;
	current->next = current->next->next;
	free(removed_node->item_name);
	free(removed_node);
	return EXIT_SUCCESS;
}
