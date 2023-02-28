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
	int status = EXIT_FAILURE;
	if (head!= NULL && filename!= NULL && strlen(filename)>0) {
		FILE *file = fopen(filename, "w");
		if (file!= NULL) {
			node *current = head;
			while (current->next!= NULL) {
				fprintf(file, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
				current = current->next;
			}
			fclose(file);
			status = EXIT_SUCCESS;
		}
	}
	return status;
}
