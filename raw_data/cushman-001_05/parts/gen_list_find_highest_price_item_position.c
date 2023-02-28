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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = head;
	int i = 0;
	float highest = 0;
	
	// traverse to end of list
	while(temp_node != NULL) {
		if(temp_node->price > highest) {
			highest = temp_node->price;
			*pos = i;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// return success
	return EXIT_SUCCESS;
}
