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
  if (head == NULL) {
    strcpy(str, "");
    return EXIT_FAILURE;
  }
  char str_price[MAX_ITEM_PRINT_LEN];
  sprintf(str_price, "%.2f", head->price);
  sprintf(str, "%d * %s @ $%s ea", head->quantity, head->item_name, str_price);
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
  int pos = 0;
  while (head != NULL) {
    char str[MAX_ITEM_PRINT_LEN];
    list_item_to_string(head, str);
    printf("%d: %s\n", ++pos, str);
    head = head->next;
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
  new_node->item_name = item_name;
  new_node->price = price;
  new_node->quantity = quantity;

  int i;
  node *curr = *head;
  node *prev = NULL;
  for (i = 0; i < pos; i++) {
    if (curr == NULL) {
      return EXIT_FAILURE;
    }
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    new_node->next = *head;
    *head = new_node;
  } else {
    new_node->next = curr;
    prev->next = new_node;
  }
  return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  int i;
  node *curr = *head;
  for (i = 0; i < pos; i++) {
    if (curr == NULL) {
      return EXIT_FAILURE;
    }
    curr = curr->next;
  }
  if (curr == NULL) {
    return EXIT_FAILURE;
  }
  curr->item_name = item_name;
  curr->price = price;
  curr->quantity = quantity;
  return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  int i;
  node *curr = *head;
  node *prev = NULL;
  for (i = 0; i < pos; i++) {
    if (curr == NULL) {
      return EXIT_FAILURE;
    }
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    *head = curr->next;
  } else {
    prev->next = curr->next;
  }
  free(curr);
  return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
  int i;
  node *curr1 = *head;
  node *curr2 = *head;
  node *prev1 = NULL;
  node *prev2 = NULL;
  for (i = 0; i < pos1; i++) {
    if (curr1 == NULL) {
      return EXIT_FAILURE;
    }
    prev1 = curr1;
    curr1 = curr1->next;
  }
  for (i = 0; i < pos2; i++) {
    if (curr2 == NULL) {
      return EXIT_FAILURE;
    }
    prev2 = curr2;
    curr2 = curr2->next;
  }
  if (curr1 == NULL || curr2 == NULL) {
    return EXIT_FAILURE;
  }
  if (prev1 == NULL) {
    *head = curr2;
  } else {
    prev1->next = curr2;
  }
  if (prev2 == NULL) {
    *head = curr1;
  } else {
    prev2->next = curr1;
  }
  node *temp = curr2->next;
  curr2->next = curr1->next;
  curr1->next = temp;
  return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  float highest_price = head->price;
  int highest_pos = 0;
  int i = 0;
  while (head != NULL) {
    if (head->price > highest_price) {
      highest_price = head->price;
      highest_pos = i;
    }
    head = head->next;
    i++;
  }
  *pos = highest_pos;
  return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  *total = 0;
  while (head != NULL) {
    *total += head->price * head->quantity;
    head = head->next;
  }
  return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    return EXIT_FAILURE;
  }

  while (head != NULL) {
    fprintf(file, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
    head = head->next;
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

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
  node *curr = *head;
  node *prev = NULL;
  while (curr != NULL) {
    int found = 0;
    node *inner_curr = curr->next;
    node *inner_prev = curr;
    while (inner_curr != NULL) {
      if (strcmp(curr->item_name, inner_curr->item_name) == 0) {
        curr->quantity += inner_curr->quantity;
        inner_prev->next = inner_curr->next;
        free(inner_curr);
        inner_curr = inner_prev->next;
        found = 1;
      } else {
        inner_prev = inner_curr;
        inner_curr = inner_curr->next;
      }
    }
    if (found) {
      if (prev == NULL) {
        *head = curr->next;
        free(curr);
        curr = *head;
      } else {
        prev->next = curr->next;
        free(curr);
        curr = prev->next;
      }
    } else {
      prev = curr;
      curr = curr->next;
    }
  }
  return EXIT_SUCCESS;
}
