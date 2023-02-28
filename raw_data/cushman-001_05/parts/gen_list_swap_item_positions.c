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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = (*head);
	int i = 0;
	
	// traverse to pos1
	while(i < pos1) {
		if(temp_node->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// set up temp node2
	node *temp_node2 = (*head);
	i = 0;
	
	// traverse to pos2
	while(i < pos2) {
		if(temp_node2->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node2 = temp_node2->next;
		i++;
	}
	
	// swap temp node and temp node2
	node *temp_node3 = temp_node->next;
	temp_node->next = temp_node2->next;
	temp_node2->next = temp_node3;
	
	// return success
	return EXIT_SUCCESS;
}
