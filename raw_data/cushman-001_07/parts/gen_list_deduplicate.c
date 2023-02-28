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
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = *head;
	node *head2 = NULL;
	node *temp2 = NULL;

	while(temp!= NULL) {
		temp2 = head2;
		head2 = malloc(sizeof(node));
		if(head2 == NULL) {
			return EXIT_FAILURE;
		}
		head2->item_name = malloc(sizeof(char) * (strlen(temp->item_name) + 1));
		strcpy(head2->item_name, temp->item_name);
		head2->price = temp->price;
		head2->quantity = temp->quantity;
		head2->next = NULL;
		if(temp2 != NULL) {
			temp2->next = head2;
		}

		temp = temp->next;
	}

	free(temp);
	*head = head2;
	return EXIT_SUCCESS;
}
