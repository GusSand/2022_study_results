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
	node *curr = *head;
	node *next = curr->next;
	
	int i = 0;
	while (curr && curr->item_name) {
		if (i == pos-1) {
			curr->item_name = item_name;
			curr->price = price;
			curr->quantity = quantity;
			return EXIT_SUCCESS;
		}
		
		curr = next;
		next = curr->next;
		
		i++;
	}
	
	return EXIT_FAILURE;
}