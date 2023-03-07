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
// to indicate whether the operation was successful or not.

// Members of the node struct:
// char* item_name, float price, int quantity, node *next

// create a new list
int list_init(node **head) {
  *head = NULL;
  return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
  char *str_ptr = str;
  char *format_str = "%d * %s @ $%.2f ea\n";

  if (head == NULL) {
    return EXIT_FAILURE;
  }
  int written_chars = sprintf(str_ptr, format_str, head->quantity, head->item_name, head->price);
  if (written_chars < 0) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// print the list to stdout
// This should be in the format of:
// "pos: quantity * item_name @ $price ea", where 
//   pos is the position of the item in the list, 
//   item_name is the item_name of the item and 
//   price is the float price of the item formatted with 2 decimal places.
// For example:
// """1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// 3: 4 * apple @ $3.00 ea
// """
// It should return a newline character at the end of each item. 
// It should not have a leading newline character.
int list_print(node *head) {
  int pos = 1;
  node *current_node = head;
  char print_str[MAX_ITEM_PRINT_LEN];
  while (current_node != NULL) {
    list_item_to_string(current_node, print_str);
    printf("%d: %s", pos, print_str);
    pos++;
    current_node = current_node->next;
  }
  return EXIT_SUCCESS;
}

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
  node *new_node = malloc(sizeof(node));
  node *current_node = *head;
  new_node->price = price;
  new_node->quantity = quantity;
  new_node->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
  strcpy(new_node->item_name, item_name);
  new_node->next = NULL;
  if (pos == 1) {
    new_node->next = *head;
    *head = new_node;
    return EXIT_SUCCESS;
  }
  for (int i = 1; i < pos - 1; i++) {
    if (current_node == NULL) {
      return EXIT_FAILURE;
    }
    current_node = current_node->next;
  }
  new_node->next = current_node->next;
  current_node->next = new_node;
  return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  node *current_node = *head;
  if (pos < 1) {
    return EXIT_FAILURE;
  }
  for (int i = 1; i < pos; i++) {
    if (current_node == NULL) {
      return EXIT_FAILURE;
    }
    current_node = current_node->next;
  }
  current_node->price = price;
  current_node->quantity = quantity;
  free(current_node->item_name);
  current_node->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
  strcpy(current_node->item_name, item_name);
  return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  node *current_node = *head;
  if (pos < 1) {
    return EXIT_FAILURE;
  }
  if (pos == 1) {
    *head = current_node->next;
    free(current_node->item_name);
    free(current_node);
    return EXIT_SUCCESS;
  }
  for (int i = 1; i < pos - 1; i++) {
    if (current_node == NULL) {
      return EXIT_FAILURE;
    }
    current_node = current_node->next;
  }
  node *node_to_remove = current_node->next;
  current_node->next = current_node->next->next;
  free(node_to_remove->item_name);
  free(node_to_remove);
  return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
  node *current_node = *head;
  node *node1 = NULL;
  node *node2 = NULL;
  node *previous_node1 = NULL;
  node *previous_node2 = NULL;
  if (pos1 < 1 || pos2 < 1) {
    return EXIT_FAILURE;
  }
  for (int i = 1; i < pos1; i++) {
    if (current_node == NULL) {
      return EXIT_FAILURE;
    }
    previous_node1 = current_node;
    current_node = current_node->next;
  }
  node1 = current_node;
  current_node = *head;
  for (int i = 1; i < pos2; i++) {
    if (current_node == NULL) {
      return EXIT_FAILURE;
    }
    previous_node2 = current_node;
    current_node = current_node->next;
  }
  node2 = current_node;
  if (pos1 == 1) {
    previous_node2->next = node1;
    node1->next = node2->next;
    node2->next = node1;
    *head = node2;
  } else if (pos2 == 1) {
    previous_node1->next = node2;
    node2->next = node1->next;
    node1->next = node2;
    *head = node1;
  } else {
    previous_node1->next = node2;
    previous_node2->next = node1;
    node1->next = node2->next;
    node2->next = node1->next;
  }
  return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  int highest_price = -1;
  node *current_node = head;
  for (int i = 1; current_node != NULL; i++) {
    if (current_node->price > highest_price) {
      highest_price = current_node->price;
      *pos = i;
    }
    current_node = current_node->next;
  }
  return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  node *current_node = head;
  *total = 0;
  for (int i = 1; current_node != NULL; i++) {
    *total += current_node->price * current_node->quantity;
    current_node = current_node->next;
  }
  return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
  FILE *file = fopen(filename, "wb");
  node *current_node = head;
  if (file == NULL) {
    return EXIT_FAILURE;
  }
  while (current_node != NULL) {
    fprintf(file, "%s,%f,%d\n", current_node->item_name, current_node->price, current_node->quantity);
    current_node = current_node->next;
  }
  fclose(file);
  return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    return EXIT_FAILURE;
  }
  node *current_node = *head;
  if (current_node == NULL) {
    return EXIT_FAILURE;
  }
  while (current_node->next != NULL) {
    current_node = current_node->next;
  }
  while (1) {
    char item_name[100];
    float price;
    int quantity;
    int num_scanned = fscanf(file, "%[^,],%f,%d\n", item_name, &price, &quantity);
    if (num_scanned == EOF) {
      break;
    }
    if (num_scanned != 3) {
      return EXIT_FAILURE;
    }
    node *new_node = malloc(sizeof(node));
    new_node->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = NULL;
    current_node->next = new_node;
    current_node = current_node->next;
  }
  fclose(file);
  return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
  node *current_node = *head;
  while (current_node != NULL) {
    node *node_to_check = current_node->next;
    while (node_to_check != NULL) {
      if (strcmp(current_node->item_name, node_to_check->item_name) == 0) {
        current_node->quantity += node_to_check->quantity;
        node *node_to_remove = node_to_check;
        node_to_check = node_to_check->next;
        list_remove_item_at_pos(head, node_to_remove->quantity);
      } else {
        node_to_check = node_to_check->next;
      }
    }
    current_node = current_node->next;
  }
  return EXIT_SUCCESS;
}
