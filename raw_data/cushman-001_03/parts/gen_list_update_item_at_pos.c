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
  // Check if pos is 0
  if (pos == 0) {
    return EXIT_FAILURE;
  }

  // Else pos is not 0
  else {
    // Check if pos is 1
      // bug 1: missing check for head == NULL
      // bug 2: missing check for *head == NULL
    if (pos == 1) {
      // bug 3: memory leak failing to free old item_name
      (*head)->item_name = malloc(strlen(item_name) + 1);
      strcpy((*head)->item_name, item_name);
      (*head)->price = price;
      (*head)->quantity = quantity;
      return EXIT_SUCCESS;
    }
    // Else pos is not 1
    else {
      // Call list_update_item_at_pos on head->next and update the result
      list_update_item_at_pos(&((*head)->next), item_name, price, quantity, pos - 1);
      // bug 4: failing to check return status
      return EXIT_SUCCESS;
    }
  }
}
