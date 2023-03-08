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
  if (head == NULL || str == NULL) {
    return EXIT_FAILURE;
  }
  snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
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
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  int count = 1;
  char str[MAX_ITEM_PRINT_LEN];
  while (head != NULL) {
    list_item_to_string(head, str);
    printf("%d: %s\n", count, str);
    head = head->next;
    count++;
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
  if (head == NULL || item_name == NULL || item_name[0] == '\0' || quantity <= 0) {
    return EXIT_FAILURE;
  }
  if (pos == 0) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item_name = (char *)malloc(sizeof(char) * (strlen(item_name) + 1));
    strcpy(new_node->item_name, item_name);
    new_node->price = price;
    new_node->quantity = quantity;
    new_node->next = *head;
    *head = new_node;
    return EXIT_SUCCESS;
  }
  node *curr = *head;
  int i = 1;
  for (i = 1; i < pos; i++) {
    if (curr->next == NULL) {
      break;
    }
    curr = curr->next;
  }
  node *new_node = (node *)malloc(sizeof(node));
  new_node->item_name = (char *)malloc(sizeof(char) * (strlen(item_name) + 1));
  strcpy(new_node->item_name, item_name);
  new_node->price = price;
  new_node->quantity = quantity;
  new_node->next = curr->next;
  curr->next = new_node;
  return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  if (head == NULL || item_name == NULL || item_name[0] == '\0' || quantity <= 0) {
    return EXIT_FAILURE;
  }
  node *curr = *head;
  int i = 1;
  for (i = 1; i < pos; i++) {
    if (curr->next == NULL) {
      return EXIT_FAILURE;
    }
    curr = curr->next;
  }
  free(curr->item_name);
  curr->item_name = (char *)malloc(sizeof(char) * (strlen(item_name) + 1));
  strcpy(curr->item_name, item_name);
  curr->price = price;
  curr->quantity = quantity;
  return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  if (pos == 0) {
    node *curr = *head;
    *head = curr->next;
    free(curr->item_name);
    free(curr);
    return EXIT_SUCCESS;
  }
  node *curr = *head;
  int i = 1;
  for (i = 1; i < pos; i++) {
    if (curr->next == NULL) {
      return EXIT_FAILURE;
    }
    curr = curr->next;
  }
  node *temp = curr->next;
  curr->next = temp->next;
  free(temp->item_name);
  free(temp);
  return EXIT_SUCCESS;
}

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

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  if (head == NULL || pos == NULL) {
    return EXIT_FAILURE;
  }
  float highest_price = head->price;
  int highest_i = 1;
  int i = 1;
  node *curr = head;
  while (curr != NULL) {
    if (curr->price > highest_price) {
      highest_price = curr->price;
      highest_i = i;
    }
    curr = curr->next;
    i++;
  }
  *pos = highest_i;
  return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  if (head == NULL || total == NULL) {
    return EXIT_FAILURE;
  }
  *total = 0;
  node *curr = head;
  while (curr != NULL) {
    *total += curr->price * curr->quantity;
    curr = curr->next;
  }
  return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
  if (head == NULL || filename == NULL || filename[0] == '\0') {
    return EXIT_FAILURE;
  }
  FILE *fptr;
  fptr = fopen(filename, "w");
  if (fptr == NULL) {
    return EXIT_FAILURE;
  }
  node *curr = head;
  while (curr != NULL) {
    fprintf(fptr, "%s,%.2f,%d\n", curr->item_name, curr->price, curr->quantity);
    curr = curr->next;
  }
  fclose(fptr);
  return EXIT_SUCCESS;
}

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

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  node *curr = *head;
  while (curr != NULL) {
    node *curr2 = curr->next;
    while (curr2 != NULL) {
      if (strcmp(curr->item_name, curr2->item_name) == 0) {
        curr->quantity += curr2->quantity;
        curr2->quantity = 0;
      }
      curr2 = curr2->next;
    }
    curr = curr->next;
  }
  curr = *head;
  node *curr2 = curr->next;
  while (curr2 != NULL) {
    if (curr2->quantity == 0) {
      curr->next = curr2->next;
      curr2->next = NULL;
      free(curr2->item_name);
      free(curr2);
      curr2 = curr->next;
    } else {
      curr = curr->next;
      curr2 = curr2->next;
    }
  }
  return EXIT_SUCCESS;
}
