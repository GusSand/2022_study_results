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
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = *head;
  if (pos1 == 1) {
    // bug 1: missing check for *head == NULL
    node *temp = current;
    current->quantity = current->quantity + current->next->quantity;
    current->price = current->price + current->next->price;
    current = current->next;
    // bug 2: missing check for next == NULL
    *head = current->next;
    current->next = temp;
    current->next->next = NULL;
  } else {
    int i = 1;
    while (current != NULL && i < pos1 - 1) {
      current = current->next;
      i++;
    }
    node *temp = current;
    current = current->next;
    temp->next = current->next;
    current->next = temp;
    // bug 3: missing check for next == NULL
    current->next->next = NULL;
  }
  // bug 4: memory leak by losing elements of the list
  return EXIT_SUCCESS;
}