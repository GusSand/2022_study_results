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
	if (pos == 1) {
		node *cur_node = *head;
		*head = (*head)->next;
		free(cur_node);
		return EXIT_SUCCESS;
	}
	node *prev_node = *head;
	node *cur_node = (*head)->next;
	unsigned int i = 2;
	while (cur_node != NULL) {
		if (i == pos) {
			prev_node->next = cur_node->next;
			free(cur_node);
			return EXIT_SUCCESS;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
		i++;
	}
	return EXIT_FAILURE;
}
