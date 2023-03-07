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
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	if(pos == 0) {
		return EXIT_FAILURE;
	}

	node *temp = *head;
	if(pos == 1) {
		if(*head == NULL) {
			return EXIT_FAILURE;
		}
		else {
			*head = temp->next;
			free(temp->item_name);
			free(temp);
			return EXIT_SUCCESS;
		}
	}

	int index = 1;
	while(temp->next!= NULL && index < pos - 1) {
		temp = temp->next;
		index++;
	}

	if(index == pos - 1) {
		if(temp->next == NULL) {
			return EXIT_FAILURE;
		}
		else {
			node *temp2 = temp->next;
			temp->next = temp->next->next;
			free(temp2->item_name);
			free(temp2);
			return EXIT_SUCCESS;
		}
	}
	else {
		return EXIT_FAILURE;
	}
}
