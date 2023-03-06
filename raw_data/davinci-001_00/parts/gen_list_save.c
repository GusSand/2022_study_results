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
// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	if (head == NULL) {
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	FILE *file = fopen(filename, "w");
	if (!file) {
		fprintf(stderr, "Couldn't open file!");
		return EXIT_FAILURE;
	}
	char *str = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	if (!str) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	node *current = head->next;
	while (current != NULL) {
		sprintf(str, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
		fputs(str, file);
		current = current->next;
	}
	fclose(file);
	return EXIT_SUCCESS;
}