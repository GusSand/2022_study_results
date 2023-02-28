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
	int status = EXIT_FAILURE;
	if (head!= NULL && *head!= NULL) {
		node *current = *head;
		node *previous = *head;
		int i = 1;
		while (current->next!= NULL && i < pos1) {
			previous = current;
			current = current->next;
			i++;
		}
		node *pos1_node = current;
		current = *head;
		previous = *head;
		i = 1;
		while (current->next!= NULL && i < pos2) {
			previous = current;
			current = current->next;
			i++;
		}
		node *pos2_node = current;
		if (pos1_node!= *head) {
			previous->next = pos2_node;
		}
		else {
			*head = pos2_node;
		}
		pos2_node->next = pos1_node->next;
		pos1_node->next = pos2_node;
		if (previous!= *head) {
			if (pos2_node->next!= NULL) {
				previous->next = pos1_node;
			}
			else {
				previous->next = NULL;
			}
		}
		status = EXIT_SUCCESS;
	}
	return status;
}
