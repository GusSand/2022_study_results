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
	}
	node *current = *head;
	int count = 1;
	while (current != NULL && count != pos1) {
		count++;
		current = current->next;
	}

	if (current == NULL) {
		return EXIT_FAILURE;
	}

	node *target = current->next;
	node *prev = current->next;
	int count2 = 1;
	while (target != NULL && count2 != pos2) {
		count2++;
		prev = target;
		target = target->next;
	}

	if (target == NULL) {
		return EXIT_FAILURE;
	}

	prev->next = target->next;
	target->next = current->next;
	current->next = target;
	return EXIT_SUCCESS;
}
