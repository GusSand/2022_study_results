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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if pos is 0
	if(pos == 0) {
		if((*head)->next == NULL) {
			free(*head);
			*head = NULL;
			return EXIT_SUCCESS;
		}
		
		node *temp_node = (*head)->next;
		free(*head);
		*head = temp_node;
		return EXIT_SUCCESS;
	}
	
	// set up temp node
	node *temp_node = *head;
	int i = 1;
	
	// traverse to pos
	while(i < pos) {
		if(temp_node->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// check if next node is NULL
	if(temp_node->next == NULL) {
		return EXIT_FAILURE;
	}
	
	// set temp node's next to next node's next
	temp_node->next = temp_node->next->next;
	
	// return success
	return EXIT_SUCCESS;
}
