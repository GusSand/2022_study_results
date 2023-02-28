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
  FILE *fp;
  char *str;
  int i = 0;
  if (!head) {
    return EXIT_FAILURE;
  }
  if ((fp = fopen(filename, "w")) == NULL) {
    return EXIT_FAILURE;
  }
  str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
  ref_list_item_to_string(head, str);
  fprintf(fp, "%s\n", str);
  while (head) {
    head = head->next;
    if (head) {
      ref_list_item_to_string(head, str);
      fprintf(fp, "%s\n", str);
    }
  }
  free(str);
  fclose(fp);
  return EXIT_SUCCESS;
}
