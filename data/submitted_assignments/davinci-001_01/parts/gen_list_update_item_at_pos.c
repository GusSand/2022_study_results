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
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
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
  while (i < pos) {
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
  if (!item_name) {
    return EXIT_SUCCESS;
  }
  // update item_name
  free(temp->item_name);
  temp->item_name = malloc(strlen(item_name) + 1);
  strcpy(temp->item_name, item_name);
  // update price
  temp->price = price;
  // update quantity
  temp->quantity = quantity;
  return EXIT_SUCCESS;
}
