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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
  if (head == NULL || filename == NULL || filename[0] == '\0') {
    return EXIT_FAILURE;
  }
  FILE *fptr;
  fptr = fopen(filename, "r");
  if (fptr == NULL) {
    return EXIT_FAILURE;
  }
  char item_name[100];
  float price;
  int quantity;
  while (fscanf(fptr, "%[^,],%f,%d\n", item_name, &price, &quantity) != EOF) {
    node *curr = *head;
    if (curr == NULL) {
      node *new_node = (node *)malloc(sizeof(node));
      new_node->item_name = (char *)malloc(sizeof(char) * (strlen(item_name) + 1));
      strcpy(new_node->item_name, item_name);
      new_node->price = price;
      new_node->quantity = quantity;
      new_node->next = NULL;
      *head = new_node;
      continue;
    }
    while (curr->next != NULL) {
      curr = curr->next;
    }
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item_name = (char *)malloc(sizeof(char) * (strlen(item_name) + 1));
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;
    curr->next = new_node;
  }
  fclose(fptr);
  return EXIT_SUCCESS;
}
