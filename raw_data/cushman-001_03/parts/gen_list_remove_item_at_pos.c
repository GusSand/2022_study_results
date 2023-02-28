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
  // Check if pos is 0
  if (pos == 0) {
    return EXIT_FAILURE;
  }

  // Else pos is not 0
  else {
    // Check if pos is 1
    if (pos == 1) {
      // bug 1: missing check for head == NULL
      // bug 2: missing check for *head == NULL
      node *temp;
      temp = *head;
      *head = (*head)->next;
      // bug 3: memory leak failing to free item_name
      free(temp);
      return EXIT_SUCCESS;
    }
    // Else pos is not 1
    else {
      // Call list_remove_item_at_pos on head->next and remove the result
      list_remove_item_at_pos(&((*head)->next), pos - 1);
      // bug 4: missing check of return status
      return EXIT_SUCCESS;
    }
  }
}
