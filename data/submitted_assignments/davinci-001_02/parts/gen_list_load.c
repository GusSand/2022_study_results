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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) {
		printf("[ERROR] cannot open file %s\n", filename);
		return EXIT_FAILURE;
	}

	char str[MAX_ITEM_PRINT_LEN];
	node *curr = *head;
	while (fgets(str, MAX_ITEM_PRINT_LEN, fp)) {
		// get item name
		char *item_name = strtok(str, ",");
		// get price
		char *price = strtok(NULL, ",");
		// get quantity
		char *quantity = strtok(NULL, ",");
		// skip newline
		char *newline = strtok(NULL, "\n");

		// create new node
		if (!(curr = (node *)malloc(sizeof(node)))) {
			printf("[ERROR] malloc failed\n");
			fclose(fp);
			return EXIT_FAILURE;
		}
		curr->next = NULL;
		curr->item_name = strdup(item_name);
		curr->price = strtof(price, NULL);
		curr->quantity = atoi(quantity);

		// add to end
		if (*head == NULL) {
			*head = curr;
		} else {
			node *tmp = *head;
			while (tmp->next) {
				tmp = tmp->next;
			}
			tmp->next = curr;
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
