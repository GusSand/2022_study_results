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
	if (fp == NULL) {
		return EXIT_FAILURE;
	}
	node *cur_node = *head;
	while (cur_node->next != NULL) {
		cur_node = cur_node->next;
	}
	char *item_name = NULL;
	float price;
	int quantity;
	while (fscanf(fp, "%m[^,],%f,%d\n", &item_name, &price, &quantity) != EOF) {
		cur_node->next = malloc(sizeof(node));
		cur_node->next->item_name = item_name;
		cur_node->next->price = price;
		cur_node->next->quantity = quantity;
		cur_node->next->next = NULL;
		cur_node = cur_node->next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
