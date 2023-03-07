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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = *head;
	
	// traverse list
	while(temp_node->next != NULL) {
		if(strcmp(temp_node->item_name, temp_node->next->item_name) == 0) {
			temp_node->quantity += temp_node->next->quantity;
			node *temp_node2 = temp_node->next;
			temp_node->next = temp_node->next->next;
			free(temp_node2);
		}
		else {
			temp_node = temp_node->next;
		}
	}
	
	// return success
	return EXIT_SUCCESS;
}
