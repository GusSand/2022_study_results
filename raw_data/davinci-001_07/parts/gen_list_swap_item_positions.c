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
	node *curr = *head;
	node *next = curr->next;
	node *swap_1 = NULL;
	node *swap_2 = NULL;
	
	int i = 0;
	while (curr && curr->item_name) {
		if (i == pos1-1) {
			swap_1 = curr;
		}
		if (i == pos2-1) {
			swap_2 = curr;
		}
		
		curr = next;
		next = curr->next;
		
		i++;
	}
	
	node *temp = swap_1->next;
	swap_1->next = swap_2->next;
	swap_2->next = temp;
	
	return EXIT_SUCCESS;
}
