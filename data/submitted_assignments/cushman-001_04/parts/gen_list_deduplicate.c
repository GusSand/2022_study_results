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
    // bug 1: missing check for head == NULL
	if(*head == NULL) {
		fprintf(stderr, "Error: list_deduplicate cannot de-duplicate an empty list.\n");
		return EXIT_FAILURE;
	}
	if((*head)->next == NULL) {
		return EXIT_SUCCESS;
	}
	node *current = *head;
	while(current->next != NULL) {
        // bug 2: missing check for item_name == NULL
		if(strcmp(current->item_name, current->next->item_name) == 0) {
			current->quantity = current->quantity + current->next->quantity;
			current->next = current->next->next;
            // bug 3: memory leak failing to free node
		}
		else {
			current = current->next;
		}
	}
	return EXIT_SUCCESS;
}
