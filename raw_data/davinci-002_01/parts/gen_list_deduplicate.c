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
	if (*head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = *head;
	while (current->next!= NULL) {
		node *next = current->next;
		while (next!= NULL) {
			if (strcmp(current->item_name, next->item_name)== 0) {
				current->quantity += next->quantity;
				ref_list_remove_item_at_pos(head, 2);
			}
			next = next->next;
		}
		current = current->next;
	}
	return EXIT_SUCCESS;
}
