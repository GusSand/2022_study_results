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
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  // bug 1: missing check for *head == NULL
  node *current = *head;
  if (pos == 1) {
    node *temp = current;
    *head = current->next;
    // bug 2: missing free of item_name
    free(temp);
  } else {
    int i = 1;
    while (current != NULL && i < pos - 1) {
      current = current->next;
      i++;
    }
    node *temp = current;
    current = current->next;
    // bug 4: missing check for next == NULL
    temp->next = current->next;
    // bug 3: missing free of item_name
    free(current);
  }
  return EXIT_SUCCESS;
}
