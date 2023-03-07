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
	node *cur_node = *head;
	while (cur_node != NULL) {
		node *cur_node2 = cur_node->next;
		node *prev_node2 = cur_node;
		while (cur_node2 != NULL) {
			if (strcmp(cur_node->item_name, cur_node2->item_name) == 0) {
				cur_node->quantity += cur_node2->quantity;
				prev_node2->next = cur_node2->next;
				free(cur_node2);
				cur_node2 = prev_node2;
			}
			prev_node2 = cur_node2;
			cur_node2 = cur_node2->next;
		}
		cur_node = cur_node->next;
	}
	return EXIT_SUCCESS;
}
