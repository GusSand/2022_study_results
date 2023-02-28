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
// print the list to stdout
// This should be in the format of:
// "pos: quantity * item_name @ $price ea", where 
//   pos is the position of the item in the list, 
//   item_name is the item_name of the item and 
//   price is the float price of the item formatted with 2 decimal places.
// For example:
// """1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// 3: 4 * apple @ $3.00 ea
// """
// It should return a newline character at the end of each item. 
// It should not have a leading newline character.
int list_print(node *head) {
	if (head == NULL) {
		printf("empty list\n");
		return EXIT_SUCCESS;
	}
	node *current = head->next;
	char *str = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	int i = 0;
	if (!str) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	while (current != NULL) {
		char *name = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		char *price = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		char *quantity = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		if (!name || !price || !quantity) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
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
		strcat(str, toPrint);
		strcat(str, "\n");
		free(toPrint);
		current = current->next;
	}
	printf("%s", str);
	free(str);
	return EXIT_SUCCESS;
}
