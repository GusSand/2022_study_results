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
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	(*head)->next = NULL;
	return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	if (head == NULL) {
		strcpy(str, "Empty list");
		return EXIT_SUCCESS;
	}

	node *current = head;
	while (current != NULL) {
		char print_str[MAX_ITEM_PRINT_LEN];
		sprintf(print_str, "%d * %s @ $%.2f ea\n", current->quantity, current->item_name, current->price);
		strcat(str, print_str);
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
	if (head == NULL) {
		printf("Empty list\n");
		return EXIT_SUCCESS;
	}
	char print_str[MAX_ITEM_PRINT_LEN];
	node *current = head;
	int count = 1;
	while (current != NULL) {
		sprintf(print_str, "%d: %d * %s @ $%.2f ea\n", count, current->quantity, current->item_name, current->price);
		printf("%s", print_str);
		count++;
		current = current->next;
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
		return EXIT_FAILURE;
	}
	node *current = *head;
	int count = 1;
	while (current != NULL && count != pos) {
		count++;
		current = current->next;
	}

	if (current == NULL) {
		return EXIT_FAILURE;
	}

	node *new_node = malloc(sizeof(node));
	new_node->item_name = item_name;
	new_node->price = price;
	new_node->quantity = quantity;
	new_node->next = current->next;
	current->next = new_node;
	return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = *head;
	int count = 1;
	while (current != NULL && count != pos) {
		count++;
		current = current->next;
	}

	if (current == NULL) {
		return EXIT_FAILURE;
	}

	current->quantity = quantity;
	current->price = price;
	current->item_name = item_name;
	return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = *head;
	int count = 1;
	while (current != NULL && count != pos) {
		count++;
		current = current->next;
	}

	if (current == NULL) {
		return EXIT_FAILURE;
	}

	node *prev = current->next;
	free(current);
	current = prev;
	return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = *head;
	int count = 1;
	while (current != NULL && count != pos1) {
		count++;
		current = current->next;
	}

	if (current == NULL) {
		return EXIT_FAILURE;
	}

	node *target = current->next;
	node *prev = current->next;
	int count2 = 1;
	while (target != NULL && count2 != pos2) {
		count2++;
		prev = target;
		target = target->next;
	}

	if (target == NULL) {
		return EXIT_FAILURE;
	}

	prev->next = target->next;
	target->next = current->next;
	current->next = target;
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = head;
	float highest_price = current->price;
	int highest_price_pos = 1;
	int count = 1;
	while (current != NULL) {
		if (current->price > highest_price) {
			highest_price = current->price;
			highest_price_pos = count;
		}
		count++;
		current = current->next;
	}
	*pos = highest_price_pos;
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = head;
	float sum = 0.0;
	while (current != NULL) {
		sum = sum + (current->price * current->quantity);
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
		return EXIT_FAILURE;
	}
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		return EXIT_FAILURE;
	}
	node *current = head;
	while (current != NULL) {
		fprintf(file, "%s,%f,%d\n", current->item_name, current->price, current->quantity);
		current = current->next;
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
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		return EXIT_FAILURE;
	}
	char line[MAX_ITEM_PRINT_LEN];
	while (fgets(line, MAX_ITEM_PRINT_LEN, file)) {
		char *token = strtok(line, ",");
		char *item_name = token;
		token = strtok(NULL, ",");
		float price = atof(token);
		token = strtok(NULL, ",");
		int quantity = atoi(token);
		node *new_node = malloc(sizeof(node));
		new_node->item_name = item_name;
		new_node->price = price;
		new_node->quantity = quantity;
		new_node->next = *head;
		*head = new_node;
	}
	fclose(file);
	return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *current = *head;
	node *prev = NULL;
	while (current != NULL) {
		node *scan = current->next;
		while (scan != NULL) {
			if (strcmp(current->item_name, scan->item_name) == 0) {
				current->quantity += scan->quantity;
				prev->next = scan->next;
				free(scan);
				scan = prev->next;
			}
			else {
				prev = scan;
				scan = scan->next;
			}
		}
		prev = current;
		current = current->next;
	}
	return EXIT_SUCCESS;
}
