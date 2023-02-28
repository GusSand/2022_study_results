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
	// If head is empty, return an empty string
	if (head == NULL) {
		str[0] = '\0';
		return EXIT_SUCCESS;
	}

	// If head has only one node
	if (head->next == NULL) {
		sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
		return EXIT_SUCCESS;
	}

	// If head has multiple nodes
	node *current = head;
	char str_curr[MAX_ITEM_PRINT_LEN];
	while (current != NULL) {
		sprintf(str_curr, "%d * %s @ $%.2f ea\n", current->quantity, current->item_name, current->price);
		strcat(str, str_curr);
		current = current->next;
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
	// If head is empty, return an empty string
	if (head == NULL) {
		printf("\n");
		return EXIT_SUCCESS;
	}

	// If head has only one node
	if (head->next == NULL) {
		printf("%d: %d * %s @ $%.2f ea\n", 1, head->quantity, head->item_name, head->price);
		return EXIT_SUCCESS;
	}

	// If head has multiple nodes
	node *current = head;
	int pos = 1;
	while (current != NULL) {
		printf("%d: %d * %s @ $%.2f ea\n", pos, current->quantity, current->item_name, current->price);
		current = current->next;
		pos++;
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
	// If pos is 0, return EXIT_FAILURE
	if (pos == 0) {
		return EXIT_FAILURE;
	}

	// If pos is 1, add to the head
	if (pos == 1) {
		node *new_node = malloc(sizeof(node));
		new_node->item_name = malloc(sizeof(item_name));
		strcpy(new_node->item_name, item_name);
		new_node->price = price;
		new_node->quantity = quantity;
		new_node->next = *head;
		*head = new_node;
		return EXIT_SUCCESS;
	}

	// If pos is greater than 1, find the node at pos - 1
	int i;
	node *current = *head;
	for (i = 1; i < pos - 1; i++) {
		current = current->next;
		if (current == NULL) {
			return EXIT_FAILURE;
		}
	}

	// Create new node with item information
	node *new_node = malloc(sizeof(node));
	new_node->item_name = malloc(sizeof(item_name));
	strcpy(new_node->item_name, item_name);
	new_node->price = price;
	new_node->quantity = quantity;

	// Insert new node into the list
	new_node->next = current->next;
	current->next = new_node;

	return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	// If pos is 0, return EXIT_FAILURE
	if (pos == 0) {
		return EXIT_FAILURE;
	}

	// If pos is 1, update the head
	if (pos == 1) {
		(*head)->item_name = item_name;
		(*head)->price = price;
		(*head)->quantity = quantity;
		return EXIT_SUCCESS;
	}

	// If pos is greater than 1, find the node at pos - 1
	int i;
	node *current = *head;
	for (i = 1; i < pos - 1; i++) {
		current = current->next;
		if (current == NULL) {
			return EXIT_FAILURE;
		}
	}

	// Update the node
	current->item_name = item_name;
	current->price = price;
	current->quantity = quantity;
	return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	// If pos is 0, return EXIT_FAILURE
	if (pos == 0) {
		return EXIT_FAILURE;
	}

	// If pos is 1, remove the head
	if (pos == 1) {
		node *temp = *head;
		*head = (*head)->next;
		free(temp->item_name);
		free(temp);
		return EXIT_SUCCESS;
	}

	// If pos is greater than 1, find the node at pos - 1
	int i;
	node *current = *head;
	for (i = 1; i < pos - 1; i++) {
		current = current->next;
		if (current == NULL) {
			return EXIT_FAILURE;
		}
	}

	// Remove the node
	node *temp = current->next;
	current->next = temp->next;
	free(temp->item_name);
	free(temp);
	return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	return EXIT_SUCCESS;
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
	return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	return EXIT_SUCCESS;
}
