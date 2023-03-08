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
// add a new item (name, price, quantity) to the list at position pos, 
//   such that the added item is the item at position pos
// For example:
// If the list is:
// 1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// and you call list_add_item_at_pos(&head, "apple", 3.0, 4, 2)
// the list should be:
// 1: 3 * banana @ $1.00 ea
// 2: 4 * apple @ $3.00 ea
// 3: 2 * orange @ $2.00 ea
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  // bug 1: missing check for head == NULL
  // bug 2: missing check for *head == NULL
  // Check if pos is 0
  if (pos == 0) {
    return EXIT_FAILURE;
  }

  // Else pos is not 0
  else {
    // Check if pos is 1
    if (pos == 1) {
      node *temp;
      temp = malloc(sizeof(node));
      // bug 3: missing check for item_name == NULL
      temp->item_name = malloc(strlen(item_name) + 1);
      strcpy(temp->item_name, item_name);
      temp->price = price;
      temp->quantity = quantity;
      temp->next = *head;
      *head = temp;
      return EXIT_SUCCESS;
    }
    // Else pos is not 1
    else {
      // Call list_add_item_at_pos on head->next and add the result
      // bug 4: missing check for return value of list_add_item_at_pos
      list_add_item_at_pos(&((*head)->next), item_name, price, quantity, pos - 1);
      return EXIT_SUCCESS;
    }
  }
}
