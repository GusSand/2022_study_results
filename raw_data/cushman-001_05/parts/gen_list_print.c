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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if item_name is NULL
	if(head->item_name == NULL) {
		return EXIT_FAILURE;
	}
	
	// print first node
	printf("%d: %d * %s @ $%0.2f ea\n", 1, head->quantity, head->item_name, head->price);
	
	// print rest of nodes
	node *temp_node = head->next;
	int pos = 2;
	while(temp_node != NULL) {
		// check if item_name is NULL
		if(temp_node->item_name == NULL) {
			return EXIT_FAILURE;
		}
		
		// print node
		printf("%d: %d * %s @ $%0.2f ea\n", pos, temp_node->quantity, temp_node->item_name, temp_node->price);
		
		// move to next node
		temp_node = temp_node->next;
		pos++;
	}
	
	// return success
	return EXIT_SUCCESS;
}
