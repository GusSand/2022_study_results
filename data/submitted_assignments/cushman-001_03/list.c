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
  // Check if head is NULL
  if (head == NULL) {
    return EXIT_FAILURE;
  }

  // Else head is not NULL
  else {
    // Check if quantity is 0
    if (head->quantity == 0) {
      return EXIT_FAILURE;
    }

    // Else quantity is not 0
    else {
      // Check if quantity is 1
      if (head->quantity == 1) {
	sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
      }

      // Else quantity is not 1
      else {
	sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
      }
    }
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
  // Check if head is NULL
  if (head == NULL) {
    return EXIT_FAILURE;
  }

  // Else head is not NULL
  else {
    // Check if head is not at the end of the list
    if (head->next != NULL) {
      // Call list_print on head->next and print the result
      list_print(head->next);
    }

    // Else head is at the end of the list
    else {
      char *str;
      char *item_name_cpy;
      str = malloc(MAX_ITEM_PRINT_LEN);
      item_name_cpy = malloc(strlen(head->item_name) + 1);
      strcpy(item_name_cpy, head->item_name);
      // Check if list_item_to_string fails
      if (list_item_to_string(head, str) == EXIT_FAILURE) {
	return EXIT_FAILURE;
      }

      // Else list_item_to_string did not fail
      else {
	printf("%s\n", str);
      }
      free(str);
      free(item_name_cpy);
    }
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
  // Check if pos is 0
  if (pos == 0) {
    return EXIT_FAILURE;
  }

  // Else pos is not 0
  else {
    // Check if pos is 1
    if (pos == 1) {
      node *temp;
      temp = malloc(sizeof(node));
      temp->item_name = malloc(strlen(item_name) + 1);
      strcpy(temp->item_name, item_name);
      temp->price = price;
      temp->quantity = quantity;
      temp->next = *head;
      *head = temp;
      return EXIT_SUCCESS;
    }
    // Else pos is not 1
    else {
      // Call list_add_item_at_pos on head->next and add the result
      list_add_item_at_pos(&((*head)->next), item_name, price, quantity, pos - 1);
      return EXIT_SUCCESS;
    }
  }
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
  // Check if pos is 0
  if (pos == 0) {
    return EXIT_FAILURE;
  }

  // Else pos is not 0
  else {
    // Check if pos is 1
    if (pos == 1) {
      (*head)->item_name = malloc(strlen(item_name) + 1);
      strcpy((*head)->item_name, item_name);
      (*head)->price = price;
      (*head)->quantity = quantity;
      return EXIT_SUCCESS;
    }
    // Else pos is not 1
    else {
      // Call list_update_item_at_pos on head->next and update the result
      list_update_item_at_pos(&((*head)->next), item_name, price, quantity, pos - 1);
      return EXIT_SUCCESS;
    }
  }
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
  // Check if pos is 0
  if (pos == 0) {
    return EXIT_FAILURE;
  }

  // Else pos is not 0
  else {
    // Check if pos is 1
    if (pos == 1) {
      node *temp;
      temp = *head;
      *head = (*head)->next;
      free(temp);
      return EXIT_SUCCESS;
    }
    // Else pos is not 1
    else {
      // Call list_remove_item_at_pos on head->next and remove the result
      list_remove_item_at_pos(&((*head)->next), pos - 1);
      return EXIT_SUCCESS;
    }
  }
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
  // Check if pos1 is 0
  if (pos1 == 0) {
    return EXIT_FAILURE;
  }

  // Check if pos2 is 0
  if (pos2 == 0) {
    return EXIT_FAILURE;
  }

  // Else pos1 and pos2 are not 0
  else {
    // Check if pos1 is 1
    if (pos1 == 1) {
      // Check if pos2 is 1
      if (pos2 == 1) {
	return EXIT_SUCCESS;
      }
      // Else pos2 is not 1
      else {
	// Call list_swap_item_positions on head->next and swap the result
	list_swap_item_positions(&((*head)->next), pos2 - 1, pos2);
	return EXIT_SUCCESS;
      }
    }
    // Else pos1 is not 1
    else {
      // Check if pos2 is 1
      if (pos2 == 1) {
	// Call list_swap_item_positions on head->next and swap the result
	list_swap_item_positions(&((*head)->next), pos1 - 1, pos1);
	return EXIT_SUCCESS;
      }
      // Else pos2 is not 1
      else {
	// Call list_swap_item_positions on head->next and swap the result
	list_swap_item_positions(&((*head)->next), pos1 - 1, pos2 - 1);
	return EXIT_SUCCESS;
      }
    }
  }
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
  // Check if head is NULL
  if (head == NULL) {
    *pos = 0;
    return EXIT_FAILURE;
  }
  // Else head is not NULL
  else {
    // Check if head->next is NULL
    if (head->next == NULL) {
      *pos = 1;
      return EXIT_SUCCESS;
    }
    // Else head->next is not NULL
    else {
      // Call list_find_highest_price_item_position on head->next and get the result
      list_find_highest_price_item_position(head->next, pos);
      // Check if the result is EXIT_FAILURE
      if (*pos == 0) {
	return EXIT_FAILURE;
      }
      // Else the result is EXIT_SUCCESS
      else {
	// Check if head->price is higher than head->next->price
	if (head->price > head->next->price) {
	  // Check if head->price is higher than head->next->next->price
	  if (head->price > (head->next->next)->price) {
	    // Check if head->price is higher than head->next->next->next->price
	    if (head->price > (head->next->next->next)->price) {
	      *pos = 1;
	      return EXIT_SUCCESS;
	    }
	    // Else head->price is not higher than head->next->next->next->price
	    else {
	      *pos = 2;
	      return EXIT_SUCCESS;
	    }
	  }
	  // Else head->price is not higher than head->next->next->price
	  else {
	    *pos = 2;
	    return EXIT_SUCCESS;
	  }
	}
	// Else head->price is not higher than head->next->price
	else {
	  *pos = 1;
	  return EXIT_SUCCESS;
	}
      }
    }
  }
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
  // Check if head is NULL
  if (head == NULL) {
    *total = 0;
    return EXIT_FAILURE;
  }
  // Else head is not NULL
  else {
    // Check if head->next is NULL
    if (head->next == NULL) {
      *total = head->price * head->quantity;
      return EXIT_SUCCESS;
    }
    // Else head->next is not NULL
    else {
      // Call list_cost_sum on head->next and get the result
      list_cost_sum(head->next, total);
      // Check if the result is EXIT_FAILURE
      if (*total == 0) {
	return EXIT_FAILURE;
      }
      // Else the result is EXIT_SUCCESS
      else {
	// Add head->price * head->quantity to the result
	*total = *total + head->price * head->quantity;
	return EXIT_SUCCESS;
      }
    }
  }
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
  // Check if head is NULL
  if (head == NULL) {
    return EXIT_FAILURE;
  }
  // Else head is not NULL
  else {
    // Check if head->next is NULL
    if (head->next == NULL) {
      FILE *fp;
      fp = fopen(filename, "w");
      if (fp == NULL) {
	return EXIT_FAILURE;
      }
      fprintf(fp, "%s,%f,%d\n", head->item_name, head->price, head->quantity);
      fclose(fp);
      return EXIT_SUCCESS;
    }
    // Else head->next is not NULL
    else {
      // Call list_save on head->next and save the result
      list_save(head->next, filename);
      // Check if head->next->next is NULL
      if (head->next->next == NULL) {
	FILE *fp;
	fp = fopen(filename, "a");
	if (fp == NULL) {
	  return EXIT_FAILURE;
	}
	fprintf(fp, "%s,%f,%d\n", head->item_name, head->price, head->quantity);
	fclose(fp);
	return EXIT_SUCCESS;
      }
      // Else head->next->next is not NULL
      else {
	// Call list_save on head->next->next and save the result
	list_save(head->next->next, filename);
	return EXIT_SUCCESS;
      }
    }
  }
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}
