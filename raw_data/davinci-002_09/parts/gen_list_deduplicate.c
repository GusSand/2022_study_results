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
  node *curr = *head;
  node *prev = NULL;
  while (curr != NULL) {
    int found = 0;
    node *inner_curr = curr->next;
    node *inner_prev = curr;
    while (inner_curr != NULL) {
      if (strcmp(curr->item_name, inner_curr->item_name) == 0) {
        curr->quantity += inner_curr->quantity;
        inner_prev->next = inner_curr->next;
        free(inner_curr);
        inner_curr = inner_prev->next;
        found = 1;
      } else {
        inner_prev = inner_curr;
        inner_curr = inner_curr->next;
      }
    }
    if (found) {
      if (prev == NULL) {
        *head = curr->next;
        free(curr);
        curr = *head;
      } else {
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
      }
    } else {
      prev = curr;
      curr = curr->next;
    }
  }
  return EXIT_SUCCESS;
}
