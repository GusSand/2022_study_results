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
	if (filename == NULL) {
		return EXIT_FAILURE;
	}

	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		return EXIT_FAILURE;
	}
	char line[MAX_ITEM_PRINT_LEN];
	unsigned int line_num = 1;
	while (fgets(line, MAX_ITEM_PRINT_LEN, file) != NULL) {
		// item_name,price,quantity\n 
		char *item_name = strtok(line, ",");
		if (item_name == NULL) {
			fclose(file);
			return EXIT_FAILURE;
		}
		char *price_string = strtok(NULL, ",");
		if (price_string == NULL) {
			fclose(file);
			return EXIT_FAILURE;
		}
		float price = atof(price_string);
		char *quantity_string = strtok(NULL, ",");
		if (quantity_string == NULL) {
			fclose(file);
			return EXIT_FAILURE;
		}
		int quantity = atoi(quantity_string);
		if (ref_list_add_item_at_pos(head, item_name, price, quantity, line_num) == EXIT_FAILURE) {
			fclose(file);
			return EXIT_FAILURE;
		}
		line_num += 1;
	}
	fclose(file);
	return EXIT_SUCCESS;
}
