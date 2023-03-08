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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  node *current_node = *head;
  if (pos < 1) {
    return EXIT_FAILURE;
  }
  if (pos == 1) {
    *head = current_node->next;
    free(current_node->item_name);
    free(current_node);
    return EXIT_SUCCESS;
  }
  for (int i = 1; i < pos - 1; i++) {
    if (current_node == NULL) {
      return EXIT_FAILURE;
    }
    current_node = current_node->next;
  }
  node *node_to_remove = current_node->next;
  current_node->next = current_node->next->next;
  free(node_to_remove->item_name);
  free(node_to_remove);
  return EXIT_SUCCESS;
}
