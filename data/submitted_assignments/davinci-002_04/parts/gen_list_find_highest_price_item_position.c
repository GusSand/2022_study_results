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
  if (head == NULL || pos == NULL) {
    return EXIT_FAILURE;
  }
  float highest_price = head->price;
  int highest_i = 1;
  int i = 1;
  node *curr = head;
  while (curr != NULL) {
    if (curr->price > highest_price) {
      highest_price = curr->price;
      highest_i = i;
    }
    curr = curr->next;
    i++;
  }
  *pos = highest_i;
  return EXIT_SUCCESS;
}
