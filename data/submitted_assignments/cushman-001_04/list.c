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
	if(*head == NULL) {
		*head = malloc(sizeof(node));
		if(!*head) {
			fprintf(stderr, "Error: list_init cannot allocate memory for head.\n");
			return EXIT_FAILURE;
		}
		(*head)->next = NULL;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	if(head->next == NULL) {
		snprintf(str, MAX_ITEM_PRINT_LEN, "%d * %s @ $%.2f ea\n", head->quantity, head->item_name, head->price);
		return EXIT_SUCCESS;
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
	node *current = head;
	int position = 1;
	if(current->next == NULL) {
		printf("%d: %d * %s @ $%.2f ea\n", position, current->quantity, current->item_name, current->price);
		return EXIT_SUCCESS;
	}
	while (current->next != NULL) {
		current = current->next;
		printf("%d: %d * %s @ $%.2f ea\n", position, current->quantity, current->item_name, current->price);
		position++;
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
	if(*head == NULL) {
		fprintf(stderr, "Error: list_add_item_at_pos cannot add an item to an empty list.\n");
		return EXIT_FAILURE;
	}
	// if pos is 0, remove the head
	if(pos == 0) {
		node *head_next = (*head)->next;
		free(*head);
		*head = head_next;
		return EXIT_SUCCESS;
	}
	// if pos is 1, add item to the beginning
	if(pos == 1) {
		node *new_node = malloc(sizeof(node));
		if(!new_node) {
			fprintf(stderr, "Error: list_add_item_at_pos cannot allocate memory for new_node.\n");
			return EXIT_FAILURE;
		}
		new_node->item_name = item_name;
		new_node->price = price;
		new_node->quantity = quantity;
		new_node->next = *head;
		*head = new_node;
		return EXIT_SUCCESS;
	}
	node *current = *head;
	for(int i = 1; i < pos - 1; i++) {
		current = current->next;
	}
	node *new_node = malloc(sizeof(node));
	if(!new_node) {
		fprintf(stderr, "Error: list_add_item_at_pos cannot allocate memory for new_node.\n");
		return EXIT_FAILURE;
	}
	new_node->item_name = item_name;
	new_node->price = price;
	new_node->quantity = quantity;
	new_node->next = current->next;
	current->next = new_node;
	return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	if(*head == NULL) {
		fprintf(stderr, "Error: list_update_item_at_pos cannot update an item in an empty list.\n");
		return EXIT_FAILURE;
	}
	if(pos == 0) {
		(*head)->item_name = item_name;
		(*head)->price = price;
		(*head)->quantity = quantity;
		return EXIT_SUCCESS;
	}
	node *current = *head;
	for(int i = 1; i < pos; i++) {
		current = current->next;
	}
	current->item_name = item_name;
	current->price = price;
	current->quantity = quantity;
	return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	if(*head == NULL) {
		fprintf(stderr, "Error: list_remove_item_at_pos cannot remove an item from an empty list.\n");
		return EXIT_FAILURE;
	}
	if(pos == 0) {
		node *head_next = (*head)->next;
		free(*head);
		*head = head_next;
		return EXIT_SUCCESS;
	}
	node *current = *head;
	for(int i = 1; i < pos - 1; i++) {
		current = current->next;
	}
	node *next = current->next->next;
	free(current->next);
	current->next = next;
	return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	if(*head == NULL) {
		fprintf(stderr, "Error: list_swap_item_positions cannot swap two items in an empty list.\n");
		return EXIT_FAILURE;
	}
	if(pos1 == 0) {
		node *head_next = (*head)->next;
		free(*head);
		*head = head_next;
		return EXIT_SUCCESS;
	}
	node *current = *head;
	for(int i = 1; i < pos1 - 1; i++) {
		current = current->next;
	}
	node *next1 = current->next;
	for(int i = 1; i < pos2 - 1; i++) {
		current = current->next;
	}
	node *next2 = current->next;
	current->next = next2;
	next1->next = next2->next;
	next2->next = next1;
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	if(head == NULL) {
		fprintf(stderr, "Error: list_find_highest_price_item_position cannot find the highest price for an empty list.\n");
		return EXIT_FAILURE;
	}
	if(head->next == NULL) {
		*pos = 0;
		return EXIT_SUCCESS;
	}
	float highest_price = head->price;
	*pos = 1;
	node *current = head->next;
	while(current != NULL) {
		if(current->price > highest_price) {
			highest_price = current->price;
			*pos = *pos + 1;
		}
		current = current->next;
	}
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	if(head == NULL) {
		fprintf(stderr, "Error: list_cost_sum cannot calculate the total cost of an empty list.\n");
		return EXIT_FAILURE;
	}
	float sum = 0;
	node *current = head;
	while(current != NULL) {
		sum = sum + current->price * current->quantity;
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
	if(head == NULL) {
		fprintf(stderr, "Error: list_save cannot save an empty list.\n");
		return EXIT_FAILURE;
	}
	FILE *fp = fopen(filename, "w");
	if(fp == NULL) {
		fprintf(stderr, "Error: list_save cannot open %s.\n", filename);
		return EXIT_FAILURE;
	}
	node *current = head;
	while(current!= NULL) {
		fprintf(fp, "%s,%f,%d\n", current->item_name, current->price, current->quantity);
		current = current->next;
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
	if(*head == NULL) {
		fprintf(stderr, "Error: list_deduplicate cannot de-duplicate an empty list.\n");
		return EXIT_FAILURE;
	}
	if((*head)->next == NULL) {
		return EXIT_SUCCESS;
	}
	node *current = *head;
	while(current->next != NULL) {
		if(strcmp(current->item_name, current->next->item_name) == 0) {
			current->quantity = current->quantity + current->next->quantity;
			current->next = current->next->next;
		}
		else {
			current = current->next;
		}
	}
	return EXIT_SUCCESS;
}
