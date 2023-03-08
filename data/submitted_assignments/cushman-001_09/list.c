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
	int status = EXIT_FAILURE;
	node *new_node = (node *)malloc(sizeof(node));
	if (new_node != NULL) {
		new_node->item_name = NULL;
		new_node->price = 0.0;
		new_node->quantity = 0;
		new_node->next = NULL;
		*head = new_node;
		status = EXIT_SUCCESS;
	}
	return status;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	int status = EXIT_FAILURE;
	if (head != NULL && str != NULL) {
		sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
		status = EXIT_SUCCESS;
	}
	return status;
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
	int status = EXIT_FAILURE;
	if (head != NULL) {
		int pos = 1;
		node *current = head->next;
		while (current != NULL) {
			char print_str[MAX_ITEM_PRINT_LEN];
			list_item_to_string(current, print_str);
			printf("%d: %s\n", pos, print_str);
			current = current->next;
			pos++;
		}
		status = EXIT_SUCCESS;
	}
	return status;
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
	int status = EXIT_FAILURE;
	if (head != NULL && *head != NULL) {
		node *current = *head;
		node *previous = *head;
		int i = 1;
		while (current->next != NULL && i < pos) {
			previous = current;
			current = current->next;
			i++;
		}
		node *new_node = (node *)malloc(sizeof(node));
		if (new_node != NULL) {
			new_node->item_name = strdup(item_name);
			new_node->price = price;
			new_node->quantity = quantity;
			new_node->next = current;
			if (current != *head) {
				previous->next = new_node;
			}
			else {
				*head = new_node;
			}
			status = EXIT_SUCCESS;
		}
	}
	return status;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	int status = EXIT_FAILURE;
	if (head != NULL && *head != NULL) {
		node *current = *head;
		int i = 1;
		while (current->next != NULL && i < pos) {
			current = current->next;
			i++;
		}
		current->item_name = strdup(item_name);
		current->price = price;
		current->quantity = quantity;
		status = EXIT_SUCCESS;
	}
	return status;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	int status = EXIT_FAILURE;
	if (head != NULL && *head != NULL) {
		node *current = *head;
		node *previous = *head;
		int i = 1;
		while (current->next != NULL && i < pos) {
			previous = current;
			current = current->next;
			i++;
		}
		if (current == *head) {
			*head = (*head)->next;
		}
		else {
			previous->next = current->next;
		}
		free(current->item_name);
		free(current);
		status = EXIT_SUCCESS;
	}
	return status;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	int status = EXIT_FAILURE;
	if (head!= NULL && *head!= NULL) {
		node *current = *head;
		node *previous = *head;
		int i = 1;
		while (current->next!= NULL && i < pos1) {
			previous = current;
			current = current->next;
			i++;
		}
		node *pos1_node = current;
		current = *head;
		previous = *head;
		i = 1;
		while (current->next!= NULL && i < pos2) {
			previous = current;
			current = current->next;
			i++;
		}
		node *pos2_node = current;
		if (pos1_node!= *head) {
			previous->next = pos2_node;
		}
		else {
			*head = pos2_node;
		}
		pos2_node->next = pos1_node->next;
		pos1_node->next = pos2_node;
		if (previous!= *head) {
			if (pos2_node->next!= NULL) {
				previous->next = pos1_node;
			}
			else {
				previous->next = NULL;
			}
		}
		status = EXIT_SUCCESS;
	}
	return status;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	int status = EXIT_FAILURE;
	if (head!= NULL && pos!= NULL) {
		node *current = head;
		float max = 0.0;
		int max_pos = 0;
		int i = 1;
		while (current->next!= NULL) {
			if (current->price > max) {
				max = current->price;
				max_pos = i;
			}
			current = current->next;
			i++;
		}
		*pos = max_pos;
		status = EXIT_SUCCESS;
	}
	return status;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	int status = EXIT_FAILURE;
	if (head!= NULL && total!= NULL) {
		node *current = head;
		float sum = 0.0;
		while (current->next!= NULL) {
			sum += current->price * current->quantity;
			current = current->next;
		}
		*total = sum;
		status = EXIT_SUCCESS;
	}
	return status;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	int status = EXIT_FAILURE;
	if (head!= NULL && filename!= NULL && strlen(filename)>0) {
		FILE *file = fopen(filename, "w");
		if (file!= NULL) {
			node *current = head;
			while (current->next!= NULL) {
				fprintf(file, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
				current = current->next;
			}
			fclose(file);
			status = EXIT_SUCCESS;
		}
	}
	return status;
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
	int status = EXIT_FAILURE;
	if (head!= NULL && *head!= NULL) {
		node *current = *head;
		node *previous = *head;
		node *next = current->next;
		while (current->next!= NULL) {
			if (strcmp(previous->item_name, current->item_name)==0) {
				previous->quantity += current->quantity;
				previous->next = next;
				free(current->item_name);
				free(current);
				current = previous;
				next = current->next;
			}
			else {
				previous = current;
				current = current->next;
				next = current->next;
			}
		}
		status = EXIT_SUCCESS;
	}
	return status;
}
