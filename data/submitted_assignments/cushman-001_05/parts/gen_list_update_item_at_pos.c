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
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if item_name is NULL
	if(item_name == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if pos is 0
	if(pos == 0) {
		*head = malloc(sizeof(node));
		(*head)->item_name = strdup(item_name);
		(*head)->price = price;
		(*head)->quantity = quantity;
		(*head)->next = NULL;
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
	
	// set temp node's item_name to item_name
	temp_node->item_name = strdup(item_name);
	
	// set temp node's price to price
	temp_node->price = price;
	
	// set temp node's quantity to quantity
	temp_node->quantity = quantity;
	
	// return success
	return EXIT_SUCCESS;
}