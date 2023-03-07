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
	if (*head == NULL) {
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	node *current = *head;
	node *pos1_node = NULL;
	node *pos2_node = NULL;
	unsigned int i = 0;
	while (current != NULL) {
		if (i == pos1 - 1) {
			pos1_node = current;
		}
		if (i == pos2 - 1) {
			pos2_node = current;
		}
		current = current->next;
		i++;
	}
	if (pos1_node == NULL || pos2_node == NULL) {
		fprintf(stderr, "No such positions!");
		return EXIT_FAILURE;
	}
	node *temp = pos1_node->next;
	pos1_node->next = pos2_node->next;
	pos2_node->next = temp;
	if (pos1 == 1) {
		*head = pos2_node;
	} else if (pos2 == 1) {
		*head = pos1_node;
	}
	return EXIT_SUCCESS;
}
