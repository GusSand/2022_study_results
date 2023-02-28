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
	FILE *fp = fopen(filename, "w");
	if (!fp) {
		printf("[ERROR] cannot open file %s\n", filename);
		return EXIT_FAILURE;
	}

	node *curr = head;
	while (curr) {
		// generate string
		char str[MAX_ITEM_PRINT_LEN];
		ref_list_item_to_string(curr, str);
		fprintf(fp, "%s\n", str);
		curr = curr->next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
