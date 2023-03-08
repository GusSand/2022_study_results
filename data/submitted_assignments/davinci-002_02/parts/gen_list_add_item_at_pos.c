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
// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 2 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	node *new_node = malloc(sizeof(node));
	if (new_node == NULL) {
		return EXIT_FAILURE;
	}
	new_node->item_name = item_name;
	new_node->price = price;
	new_node->quantity = quantity;
	if (pos == 1) {
		new_node->next = *head;
		*head = new_node;
		return EXIT_SUCCESS;
	}
	node *prev_node = *head;
	node *cur_node = (*head)->next;
	unsigned int i = 2;
	while (cur_node != NULL) {
		if (i == pos) {
			new_node->next = cur_node;
			prev_node->next = new_node;
			return EXIT_SUCCESS;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
		i++;
	}
	if (i == pos) {
		prev_node->next = new_node;
		new_node->next = NULL;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
