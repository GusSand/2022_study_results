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
// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	// If head is empty, return an empty string
	if (head == NULL) {
		str[0] = '\0';
		return EXIT_SUCCESS;
	}

	// If head has only one node
	if (head->next == NULL) {
		sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
		return EXIT_SUCCESS;
	}

	// If head has multiple nodes
	node *current = head;
	char str_curr[MAX_ITEM_PRINT_LEN];
	while (current != NULL) {
		sprintf(str_curr, "%d * %s @ $%.2f ea\n", current->quantity, current->item_name, current->price);
		strcat(str, str_curr);
		current = current->next;
	}

	return EXIT_SUCCESS;
}
