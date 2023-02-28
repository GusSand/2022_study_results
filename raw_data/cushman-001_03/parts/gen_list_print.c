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
// print the list to stdout
// This should be in the format of:
// "pos: quantity * item_name @ $price ea", where 
//   pos is the position of the item in the list, 
//   item_name is the item_name of the item and 
//   price is the float price of the item formatted with 2 decimal places.
// For example:
// """1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// 3: 4 * apple @ $3.00 ea
// """
// It should return a newline character at the end of each item. 
// It should not have a leading newline character.
int list_print(node *head) {
  // Check if head is NULL
  if (head == NULL) {
    return EXIT_FAILURE;
  }

  // Else head is not NULL
  else {
    // Check if head is not at the end of the list
    if (head->next != NULL) {
      // Call list_print on head->next and print the result
      list_print(head->next);
      // bug 1: missing check of return status
    }

    // Else head is at the end of the list
    else {
      char *str;
      char *item_name_cpy;
      str = malloc(MAX_ITEM_PRINT_LEN);
      // bug 2: missing check for item_name == NULL
      item_name_cpy = malloc(strlen(head->item_name) + 1);
      strcpy(item_name_cpy, head->item_name);
      // Check if ref_list_item_to_string fails
      if (ref_list_item_to_string(head, str) == EXIT_FAILURE) {
	return EXIT_FAILURE;
      }

      // Else ref_list_item_to_string did not fail
      else {
	printf("%s\n", str);
      }
      free(str);
      free(item_name_cpy);
    }
  }
  return EXIT_SUCCESS;
}
