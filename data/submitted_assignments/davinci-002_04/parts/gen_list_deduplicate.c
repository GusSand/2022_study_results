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
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  node *curr = *head;
  while (curr != NULL) {
    node *curr2 = curr->next;
    while (curr2 != NULL) {
      if (strcmp(curr->item_name, curr2->item_name) == 0) {
        curr->quantity += curr2->quantity;
        curr2->quantity = 0;
      }
      curr2 = curr2->next;
    }
    curr = curr->next;
  }
  curr = *head;
  node *curr2 = curr->next;
  while (curr2 != NULL) {
    if (curr2->quantity == 0) {
      curr->next = curr2->next;
      curr2->next = NULL;
      free(curr2->item_name);
      free(curr2);
      curr2 = curr->next;
    } else {
      curr = curr->next;
      curr2 = curr2->next;
    }
  }
  return EXIT_SUCCESS;
}
