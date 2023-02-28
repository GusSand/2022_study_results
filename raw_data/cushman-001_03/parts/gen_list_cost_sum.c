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
// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  // Check if head is NULL
  if (head == NULL) {
    // bug 1: missing check for total == NULL
    *total = 0;
    return EXIT_FAILURE;
  }
  // Else head is not NULL
  else {
    // Check if head->next is NULL
    if (head->next == NULL) {
      // bug 2: missing check for total == NULL
      *total = head->price * head->quantity;
      return EXIT_SUCCESS;
    }
    // Else head->next is not NULL
    else {
      // Call list_cost_sum on head->next and get the result
      list_cost_sum(head->next, total);
      // bug 5: missing check of return status
      // Check if the result is EXIT_FAILURE
      // bug 3: missing check for total == NULL
      if (*total == 0) {
	return EXIT_FAILURE;
      }
      // Else the result is EXIT_SUCCESS
      else {
	// Add head->price * head->quantity to the result
    // bug 4: missing check for total == NULL
	*total = *total + head->price * head->quantity;
	return EXIT_SUCCESS;
      }
    }
  }
}
