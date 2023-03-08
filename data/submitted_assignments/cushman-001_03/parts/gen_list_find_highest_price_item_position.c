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
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  // Check if head is NULL
  if (head == NULL) {
    // bug 1: missing check for pos == NULL
    *pos = 0;
    return EXIT_FAILURE;
  }
  // Else head is not NULL
  else {
    // Check if head->next is NULL
    if (head->next == NULL) {
      // bug 2: missing check for pos == NULL
      *pos = 1;
      return EXIT_SUCCESS;
    }
    // Else head->next is not NULL
    else {
      // Call list_find_highest_price_item_position on head->next and get the result
      // bug 3: missing check for return value
      list_find_highest_price_item_position(head->next, pos);
      // Check if the result is EXIT_FAILURE
      // bug 4: missing check for pos == NULL
      if (*pos == 0) {
	return EXIT_FAILURE;
      }
      // Else the result is EXIT_SUCCESS
      else {
	// Check if head->price is higher than head->next->price
	if (head->price > head->next->price) {
	  // Check if head->price is higher than head->next->next->price
      // bug 9: missing check for next == NULL
	  if (head->price > (head->next->next)->price) {
	    // Check if head->price is higher than head->next->next->next->price
        // bug 10: missing check for next == NULL
	    if (head->price > (head->next->next->next)->price) {
          // bug 5: missing check for pos == NULL
	      *pos = 1;
	      return EXIT_SUCCESS;
	    }
	    // Else head->price is not higher than head->next->next->next->price
	    else {
          // bug 6: missing check for pos == NULL
	      *pos = 2;
	      return EXIT_SUCCESS;
	    }
	  }
	  // Else head->price is not higher than head->next->next->price
	  else {
        // bug 7: missing check for pos == NULL
	    *pos = 2;
	    return EXIT_SUCCESS;
	  }
	}
	// Else head->price is not higher than head->next->price
	else {
      // bug 8: missing check for pos == NULL
	  *pos = 1;
	  return EXIT_SUCCESS;
	}
      }
    }
  }
}
