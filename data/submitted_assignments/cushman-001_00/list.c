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
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
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
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  int i = 1;
  while (head != NULL) {
    char print_str[MAX_ITEM_PRINT_LEN];
    list_item_to_string(head, print_str);
    printf("%d: %s\n", i, print_str);
    head = head->next;
    i++;
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
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = *head;
  if (pos == 1) {
    current->quantity += quantity;
    current->price += (price * quantity);
  } else {
    int i = 1;
    while (current != NULL && i < pos) {
      current = current->next;
      i++;
    }
    current->quantity += quantity;
    current->price += (price * quantity);
  }
  return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = *head;
  if (pos == 1) {
    current->quantity = quantity;
    current->price = price;
  } else {
    int i = 1;
    while (current != NULL && i < pos) {
      current = current->next;
      i++;
    }
    current->quantity = quantity;
    current->price = price;
  }
  return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = *head;
  if (pos == 1) {
    node *temp = current;
    *head = current->next;
    free(temp);
  } else {
    int i = 1;
    while (current != NULL && i < pos - 1) {
      current = current->next;
      i++;
    }
    node *temp = current;
    current = current->next;
    temp->next = current->next;
    free(current);
  }
  return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = *head;
  if (pos1 == 1) {
    node *temp = current;
    current->quantity = current->quantity + current->next->quantity;
    current->price = current->price + current->next->price;
    current = current->next;
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
    current->next->next = NULL;
  }
  return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = head;
  int i = 1;
  float max = 0;
  while (current!= NULL) {
    if (current->price > max) {
      max = current->price;
      *pos = i;
    }
    current = current->next;
    i++;
  }
  return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = head;
  float sum = 0;
  while (current!= NULL) {
    sum += current->price;
    current = current->next;
  }
  *total = sum;
  return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  FILE *fp;
  if ((fp = fopen(filename, "w")) == NULL) {
    printf("Error: file cannot be opened\n");
    return EXIT_FAILURE;
  }
  while (head!= NULL) {
    char print_str[MAX_ITEM_PRINT_LEN];
    list_item_to_string(head, print_str);
    fprintf(fp, "%s", print_str);
    head = head->next;
  }
  fclose(fp);
  return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
  if (head == NULL) {
    printf("Error: list is empty\n");
    return EXIT_FAILURE;
  }
  node *current = *head;
  node *next = current->next;
  node *prev = current;
  while (next != NULL) {
    if (strcmp(current->item_name, next->item_name) == 0) {
      current->quantity += next->quantity;
      current->price += next->price;
      prev->next = next->next;
      free(next);
    } else {
      prev = current;
      current = current->next;
    }
    next = current->next;
  }
  return EXIT_SUCCESS;
}
