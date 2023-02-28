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
  node *current_node = *head;
  while (current_node != NULL) {
    node *node_to_check = current_node->next;
    while (node_to_check != NULL) {
      if (strcmp(current_node->item_name, node_to_check->item_name) == 0) {
        current_node->quantity += node_to_check->quantity;
        node *node_to_remove = node_to_check;
        node_to_check = node_to_check->next;
        ref_list_remove_item_at_pos(head, node_to_remove->quantity);
      } else {
        node_to_check = node_to_check->next;
      }
    }
    current_node = current_node->next;
  }
  return EXIT_SUCCESS;
}
