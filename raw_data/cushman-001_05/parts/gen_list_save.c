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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = head;
	
	// open file
	FILE *f = fopen(filename, "w");
	
	// check if file is NULL
	if(f == NULL) {
		return EXIT_FAILURE;
	}
	
	// write to file
	while(temp_node != NULL) {
		fprintf(f, "%s,%f,%d\n", temp_node->item_name, temp_node->price, temp_node->quantity);
		temp_node = temp_node->next;
	}
	
	// close file
	fclose(f);
	
	// return success
	return EXIT_SUCCESS;
}
