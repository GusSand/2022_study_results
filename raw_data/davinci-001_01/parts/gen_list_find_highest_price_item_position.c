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
  node *temp = head;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // find the highest price node
  while (temp->next) {
    if (temp->price > temp->next->price) {
      temp = temp->next;
    }
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  *pos = temp->next->next - temp->next;
  return EXIT_SUCCESS;
}
