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
  *head = malloc(sizeof(node));
  if (!*head) {
    return EXIT_FAILURE;
  }
  (*head)->item_name = NULL;
  (*head)->price = 0;
  (*head)->quantity = 0;
  (*head)->next = NULL;
  return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no head
  if (!head->item_name) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!head->next) {
    // if there is only one item
    if (head->quantity > 1) {
      // if quantity is greater than 1
      snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
      return EXIT_SUCCESS;
    } else {
      // if quantity is 1
      snprintf(str, MAX_ITEM_PRINT_LEN, "%s @ $%.2f ea", head->item_name, head->price);
      return EXIT_SUCCESS;
    }
  }
  // if there is more than one item
  // check if there is no next node
  if (head->quantity > 1) {
    // if quantity is greater than 1
    snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
  } else {
    // if quantity is 1
    snprintf(str, MAX_ITEM_PRINT_LEN, "%s @ $%.2f ea", head->item_name, head->price);
    return EXIT_SUCCESS;
  }
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
  int i = 0;
  char *str;
  if (!head) {
    return EXIT_SUCCESS;
  }
  snprintf(str, MAX_ITEM_PRINT_LEN, "%d", i);
  // check if there is no head
  if (!head->item_name) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!head->next) {
    // if there is only one item
    if (head->quantity > 1) {
      // if quantity is greater than 1
      printf("%s: %d * %s @ $%.2f ea\n", str, head->quantity, head->item_name, head->price);
      return EXIT_SUCCESS;
    } else {
      // if quantity is 1
      printf("%s: %s @ $%.2f ea\n", str, head->item_name, head->price);
      return EXIT_SUCCESS;
    }
  }
  // if there is more than one item
  // check if there is no next node
  if (head->quantity > 1) {
    // if quantity is greater than 1
    printf("%s: %d * %s @ $%.2f ea\n", str, head->quantity, head->item_name, head->price);
    return EXIT_SUCCESS;
  } else {
    // if quantity is 1
    printf("%s: %s @ $%.2f ea\n", str, head->item_name, head->price);
    return EXIT_SUCCESS;
  }
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
  node *temp = *head;
  unsigned int i = 0;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no item_name
  if (!temp) {
    return EXIT_SUCCESS;
  }
  while (i < pos) {
    // check if there is no next node
    if (!temp->next) {
      return EXIT_SUCCESS;
    }
    temp = temp->next;
    i++;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!item_name) {
    return EXIT_SUCCESS;
  }
  node *new_node = malloc(sizeof(node));
  new_node->item_name = malloc(strlen(item_name) + 1);
  strcpy(new_node->item_name, item_name);
  new_node->price = price;
  new_node->quantity = quantity;
  new_node->next = temp->next;
  temp->next = new_node;
  return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  node *temp = *head;
  unsigned int i = 0;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no item_name
  if (!temp) {
    return EXIT_SUCCESS;
  }
  while (i < pos) {
    // check if there is no next node
    if (!temp->next) {
      return EXIT_SUCCESS;
    }
    temp = temp->next;
    i++;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!item_name) {
    return EXIT_SUCCESS;
  }
  // update item_name
  free(temp->item_name);
  temp->item_name = malloc(strlen(item_name) + 1);
  strcpy(temp->item_name, item_name);
  // update price
  temp->price = price;
  // update quantity
  temp->quantity = quantity;
  return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  node *temp = *head;
  unsigned int i = 0;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no item_name
  if (!temp) {
    return EXIT_SUCCESS;
  }
  while (i < pos) {
    // check if there is no next node
    if (!temp->next) {
      return EXIT_SUCCESS;
    }
    temp = temp->next;
    i++;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  node *new_node = malloc(sizeof(node));
  new_node = temp->next;
  temp->next = new_node->next;
  free(new_node);
  return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
  node *temp = *head;
  unsigned int i = 0;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no item_name
  if (!temp) {
    return EXIT_SUCCESS;
  }
  while (i < pos1) {
    // check if there is no next node
    if (!temp->next) {
      return EXIT_SUCCESS;
    }
    temp = temp->next;
    i++;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  node *temp1 = temp;
  node *temp2 = temp;
  while (i < pos2) {
    // check if there is no next node
    if (!temp2->next) {
      return EXIT_SUCCESS;
    }
    temp2 = temp2->next;
    i++;
  }
  // check if there is no next node
  if (!temp2->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp2->item_name) {
    return EXIT_SUCCESS;
  }
  temp1->next = temp2->next;
  temp2->next = temp;
  temp = temp2;
  return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  node *temp = head;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // find the highest price node
  while (temp->next) {
    if (temp->price > temp->next->price) {
      temp = temp->next;
    }
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  *pos = temp->next->next - temp->next;
  return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  node *temp = head;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no item_name
  if (!temp) {
    return EXIT_SUCCESS;
  }
  *total = 0.0;
  // calculate the total cost
  while (temp) {
    *total += (temp->price * temp->quantity);
    temp = temp->next;
  }
  return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
  FILE *fp;
  char *str;
  int i = 0;
  if (!head) {
    return EXIT_FAILURE;
  }
  if ((fp = fopen(filename, "w")) == NULL) {
    return EXIT_FAILURE;
  }
  str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
  list_item_to_string(head, str);
  fprintf(fp, "%s\n", str);
  while (head) {
    head = head->next;
    if (head) {
      list_item_to_string(head, str);
      fprintf(fp, "%s\n", str);
    }
  }
  free(str);
  fclose(fp);
  return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL) {
    return EXIT_FAILURE;
  }
  char *str = malloc(MAX_ITEM_PRINT_LEN * sizeof(char));
  while (fgets(str, MAX_ITEM_PRINT_LEN, fp)) {
    char *p_char = str;
    unsigned int i = 0;
    node *temp = *head;
    while (*p_char != ',') {
      p_char++;
      i++;
    }
    *p_char = '\0';
    p_char++;
    char *p_char2 = p_char;
    while (*p_char2 != ',') {
      p_char2++;
      i++;
    }
    *p_char2 = '\0';
    p_char2++;
    float price = atof(p_char);
    int quantity = atoi(p_char2);
    list_add_item_at_pos(head, str, price, quantity, i);
  }
  free(str);
  fclose(fp);
  return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
  node *temp = *head;
  // check if there is no head
  if (!head) {
    return EXIT_FAILURE;
  }
  // check if there is no next node
  if (!temp->next) {
    return EXIT_SUCCESS;
  }
  // check if there is no item_name
  if (!temp->item_name) {
    return EXIT_SUCCESS;
  }
  // de-duplicate the list
  while (temp->next) {
    if (strcmp(temp->item_name, temp->next->item_name) == 0) {
      temp->quantity += temp->next->quantity;
      temp->next = temp->next->next;
    } else {
      temp = temp->next;
    }
  }
  return EXIT_SUCCESS;
}
