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
	if (*head == NULL) {
		ref_list_init(head);
	}
	node *current = *head;
	FILE *file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "Couldn't open file!");
		return EXIT_FAILURE;
	}
	char *line = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	if (!line) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	while (fgets(line, MAX_ITEM_PRINT_LEN, file) != NULL) {
		node *new = malloc(sizeof(node));
		if (!new) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		char *token[3];
		int i = 0;
		char *next = line;
		while (next[i] != '\n') {
			token[i] = next;
			i++;
			next = next + 1;
		}
		token[i] = next;
		i++;
		new->item_name = malloc(sizeof(char) * (strlen(token[0]) - 1));
		if (!new->item_name) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		strcpy(new->item_name, token[0]);
		new->price = strtod(token[1], NULL);
		new->quantity = atoi(token[2]);
		new->next = NULL;
		current->next = new;
		current = new;
	}
	fclose(file);
	return EXIT_SUCCESS;
}
