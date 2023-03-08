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
	if (head == NULL) {
		strcpy(str, "Empty list");
		return EXIT_SUCCESS;
	}

	node *current = head;
	while (current != NULL) {
		char print_str[MAX_ITEM_PRINT_LEN];
		sprintf(print_str, "%d * %s @ $%.2f ea\n", current->quantity, current->item_name, current->price);
		strcat(str, print_str);
		current = current->next;
	}
	return EXIT_SUCCESS;
}
