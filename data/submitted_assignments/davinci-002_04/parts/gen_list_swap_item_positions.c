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
    return EXIT_FAILURE;
  }
  node *curr1 = *head;
  node *curr2 = *head;
  int i = 1;
  for (i = 1; i < pos1; i++) {
    if (curr1->next == NULL) {
      return EXIT_FAILURE;
    }
    curr1 = curr1->next;
  }
  for (i = 1; i < pos2; i++) {
    if (curr2->next == NULL) {
      return EXIT_FAILURE;
    }
    curr2 = curr2->next;
  }
  char *temp_item_name = (char *)malloc(sizeof(char) * (strlen(curr1->item_name) + 1));
  strcpy(temp_item_name, curr1->item_name);
  float temp_price = curr1->price;
  int temp_quantity = curr1->quantity;
  free(curr1->item_name);
  curr1->item_name = (char *)malloc(sizeof(char) * (strlen(curr2->item_name) + 1));
  strcpy(curr1->item_name, curr2->item_name);
  curr1->price = curr2->price;
  curr1->quantity = curr2->quantity;
  free(curr2->item_name);
  curr2->item_name = (char *)malloc(sizeof(char) * (strlen(temp_item_name) + 1));
  strcpy(curr2->item_name, temp_item_name);
  curr2->price = temp_price;
  curr2->quantity = temp_quantity;
  free(temp_item_name);
  return EXIT_SUCCESS;
}
