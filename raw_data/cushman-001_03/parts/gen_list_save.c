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
  // Check if head is NULL
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  // Else head is not NULL
  else {
    // Check if head->next is NULL
    if (head->next == NULL) {
      FILE *fp;
      // bug 1: missing check for filename == NULL
      fp = fopen(filename, "w");
      if (fp == NULL) {
	return EXIT_FAILURE;
      }
      // bug 2: missing check for item_name == NULL
      fprintf(fp, "%s,%f,%d\n", head->item_name, head->price, head->quantity);
      // bug 3: missing check of return status
      fclose(fp);
      return EXIT_SUCCESS;
    }
    // Else head->next is not NULL
    else {
      // Call list_save on head->next and save the result
      list_save(head->next, filename);
      // bug 4: missing check of return status
      // Check if head->next->next is NULL
      if (head->next->next == NULL) {
	FILE *fp;
      // bug 5: missing check for filename == NULL
	fp = fopen(filename, "a");
	if (fp == NULL) {
	  return EXIT_FAILURE;
	}
    // bug 6: missing check for item_name == NULL
	fprintf(fp, "%s,%f,%d\n", head->item_name, head->price, head->quantity);
    // bug 7: missing check of return status
	fclose(fp);
	return EXIT_SUCCESS;
      }
      // Else head->next->next is not NULL
      else {
	// Call list_save on head->next->next and save the result
	list_save(head->next->next, filename);
    // bug 8: missing check of return status
	return EXIT_SUCCESS;
      }
    }
  }
}
