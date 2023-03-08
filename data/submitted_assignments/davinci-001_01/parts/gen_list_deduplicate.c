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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
  node *temp = *head;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  // de-duplicate the list
  while (temp->next) {
    if (strcmp(temp->item_name, temp->next->item_name) == 0) {
      temp->quantity += temp->next->quantity;
      temp->next = temp->next->next;
    } else {
      temp = temp->next;
    }
  }
  return EXIT_SUCCESS;
}
