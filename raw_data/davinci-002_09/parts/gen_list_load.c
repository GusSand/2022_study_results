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
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return EXIT_FAILURE;
  }

  node *new_node = *head;
  while (new_node != NULL && new_node->next != NULL) {
    new_node = new_node->next;
  }

  char line[100];
  while (fgets(line, 100, file) != NULL) {
    if (new_node == NULL) {
      new_node = malloc(sizeof(node));
      *head = new_node;
    } else {
      new_node->next = malloc(sizeof(node));
      new_node = new_node->next;
    }
    char *item_name = strtok(line, ",");
    new_node->item_name = malloc(strlen(item_name) + 1);
    strcpy(new_node->item_name, item_name);
    new_node->price = atof(strtok(NULL, ","));
    new_node->quantity = atoi(strtok(NULL, "\n"));
    new_node->next = NULL;
  }
  fclose(file);
  return EXIT_SUCCESS;
}
