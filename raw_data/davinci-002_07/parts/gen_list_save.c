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
  FILE *file = fopen(filename, "wb");
  node *current_node = head;
  if (file == NULL) {
    return EXIT_FAILURE;
  }
  while (current_node != NULL) {
    fprintf(file, "%s,%f,%d\n", current_node->item_name, current_node->price, current_node->quantity);
    current_node = current_node->next;
  }
  fclose(file);
  return EXIT_SUCCESS;
}
