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
		strcpy(str, "empty list");
		return EXIT_SUCCESS;
	}
	node *current = head->next;
	char *name = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	char *price = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	char *quantity = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	int i = 0;
	if (!name || !price || !quantity) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	while (current != NULL) {
		sprintf(name, "%s", current->item_name);
		sprintf(price, "%.2f", current->price);
		sprintf(quantity, "%d", current->quantity);
		char *toPrint = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		if (!toPrint) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		strcat(toPrint, quantity);
		strcat(toPrint, " * ");
		strcat(toPrint, name);
		strcat(toPrint, " @ $");
		strcat(toPrint, price);
		strcat(toPrint, " ea");
		strcpy(str + i, toPrint);
		i += strlen(toPrint);
		strcat(str, "\n");
		free(toPrint);
		current = current->next;
	}
	free(name);
	free(price);
	free(quantity);
	return EXIT_SUCCESS;
}
