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
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		return EXIT_FAILURE;
	}
	char line[MAX_ITEM_PRINT_LEN];
	while (fgets(line, MAX_ITEM_PRINT_LEN, file)) {
		char *token = strtok(line, ",");
		char *item_name = token;
		token = strtok(NULL, ",");
		float price = atof(token);
		token = strtok(NULL, ",");
		int quantity = atoi(token);
		node *new_node = malloc(sizeof(node));
		new_node->item_name = item_name;
		new_node->price = price;
		new_node->quantity = quantity;
		new_node->next = *head;
		*head = new_node;
	}
	fclose(file);
	return EXIT_SUCCESS;
}
