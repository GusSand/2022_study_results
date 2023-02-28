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
	node *curr = *head;
	FILE *fptr = fopen(filename, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token, *saveptr;
	char *item_name, *price_string, *quantity_string;
	float price, quantity;
	
	if (!fptr) return EXIT_FAILURE;
	
	while ((read = getline(&line, &len, fptr)) != -1) {
		if (line[0] == '#') {
			// skip comments
			continue;
		}
		
		token = strtok_r(line, ",", &saveptr);
		item_name = token;
		token = strtok_r(NULL, ",", &saveptr);
		price_string = token;
		token = strtok_r(NULL, ",", &saveptr);
		quantity_string = token;
		
		price = atof(price_string);
		quantity = atoi(quantity_string);
		
		ref_list_add_item_at_pos(head, item_name, price, quantity, 0);
	}
	
	fclose(fptr);
	free(line);
	
	return EXIT_SUCCESS;
}
