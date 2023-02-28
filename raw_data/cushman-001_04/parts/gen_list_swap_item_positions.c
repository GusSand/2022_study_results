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
    // bug 1: missing check for head == NULL
	if(*head == NULL) {
		fprintf(stderr, "Error: list_swap_item_positions cannot swap two items in an empty list.\n");
		return EXIT_FAILURE;
	}
	if(pos1 == 0) {
		node *head_next = (*head)->next;
        // bug 2: memory leak failing to free item_name
		free(*head);
		*head = head_next;
		return EXIT_SUCCESS;
	}
	node *current = *head;
	for(int i = 1; i < pos1 - 1; i++) {
        // bug 3: missing check for next == NULL
		current = current->next;
	}
	node *next1 = current->next;
	for(int i = 1; i < pos2 - 1; i++) {
        // bug 4: missing check for next == NULL
		current = current->next;
	}
    // bug 5: memory leak losing elements of the list
    // bug 6: corrupts list to have circular reference when pos1 == pos2
	node *next2 = current->next;
	current->next = next2;
    // bug 7: missing check for next == NULL
	next1->next = next2->next;
	next2->next = next1;
	return EXIT_SUCCESS;
}
