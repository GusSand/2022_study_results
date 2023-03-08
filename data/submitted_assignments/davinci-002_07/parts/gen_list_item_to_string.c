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
// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
  char *str_ptr = str;
  char *format_str = "%d * %s @ $%.2f ea\n";

  if (head == NULL) {
    return EXIT_FAILURE;
  }
  int written_chars = sprintf(str_ptr, format_str, head->quantity, head->item_name, head->price);
  if (written_chars < 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
