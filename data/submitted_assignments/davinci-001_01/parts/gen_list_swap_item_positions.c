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
  node *temp = *head;
  unsigned int i = 0;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no item_name
  if (!temp) {
    return EXIT_SUCCESS;
  }
  while (i < pos1) {
    // check if there is no next node
    if (!temp->next) {
      return EXIT_SUCCESS;
    }
    temp = temp->next;
    i++;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  node *temp1 = temp;
  node *temp2 = temp;
  while (i < pos2) {
    // check if there is no next node
    if (!temp2->next) {
      return EXIT_SUCCESS;
    }
    temp2 = temp2->next;
    i++;
  }
  // check if there is no next node
  if (!temp2->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp2->item_name) {
    return EXIT_SUCCESS;
  }
  temp1->next = temp2->next;
  temp2->next = temp;
  temp = temp2;
  return EXIT_SUCCESS;
}
