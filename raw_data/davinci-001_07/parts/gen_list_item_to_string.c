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
	node *curr = head;
	char *item_name = curr->item_name;
	char *price_string = malloc(MAX_ITEM_PRINT_LEN);
	float price = curr->price;
	int quantity = curr->quantity;
	
	if (!str || !item_name || !price_string) return EXIT_FAILURE;
	
	sprintf(price_string, "%.2f", price);
	sprintf(str, "%d * %s @ $%s ea", quantity, item_name, price_string);
	
	return EXIT_SUCCESS;
}
