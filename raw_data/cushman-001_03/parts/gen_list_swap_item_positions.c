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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
  // bug 1: missing check for head == NULL
  // bug 2: missing check for *head == NULL
  // Check if pos1 is 0
  if (pos1 == 0) {
    return EXIT_FAILURE;
  }

  // Check if pos2 is 0
  if (pos2 == 0) {
    return EXIT_FAILURE;
  }

  // Else pos1 and pos2 are not 0
  else {
    // Check if pos1 is 1
    if (pos1 == 1) {
      // Check if pos2 is 1
      if (pos2 == 1) {
	return EXIT_SUCCESS;
      }
      // Else pos2 is not 1
      else {
	// Call list_swap_item_positions on head->next and swap the result
	list_swap_item_positions(&((*head)->next), pos2 - 1, pos2);
    // bug 3: missing check of return status
	return EXIT_SUCCESS;
      }
    }
    // Else pos1 is not 1
    else {
      // Check if pos2 is 1
      if (pos2 == 1) {
	// Call list_swap_item_positions on head->next and swap the result
	list_swap_item_positions(&((*head)->next), pos1 - 1, pos1);
    // bug 4: missing check of return status
	return EXIT_SUCCESS;
      }
      // Else pos2 is not 1
      else {
	// Call list_swap_item_positions on head->next and swap the result
	list_swap_item_positions(&((*head)->next), pos1 - 1, pos2 - 1);
    // bug 5: missing check of return status
	return EXIT_SUCCESS;
      }
    }
  }
}
