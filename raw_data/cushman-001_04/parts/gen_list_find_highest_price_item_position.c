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
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	if(head == NULL) {
		fprintf(stderr, "Error: list_find_highest_price_item_position cannot find the highest price for an empty list.\n");
		return EXIT_FAILURE;
	}
	if(head->next == NULL) {
        // bug 1: missing check for pos == NULL
		*pos = 0;
		return EXIT_SUCCESS;
	}
	float highest_price = head->price;
    // bug 2: missing check for pos == NULL
	*pos = 1;
	node *current = head->next;
	while(current != NULL) {
		if(current->price > highest_price) {
			highest_price = current->price;
			*pos = *pos + 1;
		}
		current = current->next;
	}
	return EXIT_SUCCESS;
}
