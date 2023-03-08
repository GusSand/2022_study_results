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
	if (!head) return EXIT_FAILURE;
	
	*head = malloc(sizeof(node));
	if (!*head) return EXIT_FAILURE;
	
	(*head)->next = NULL;
	
	return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	node *curr = head;
	char *item_name = curr->item_name;
	char *price_string = malloc(MAX_ITEM_PRINT_LEN);
	float price = curr->price;
	int quantity = curr->quantity;
	
	if (!str || !item_name || !price_string) return EXIT_FAILURE;
	
	sprintf(price_string, "%.2f", price);
	sprintf(str, "%d * %s @ $%s ea", quantity, item_name, price_string);
	
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
	node *curr = head;
	int pos = 1;
	char *str = malloc(MAX_ITEM_PRINT_LEN * 3);
	
	if (!str) return EXIT_FAILURE;
	
	while (curr) {
		list_item_to_string(curr, str);
		printf("%d: %s\n", pos, str);
		curr = curr->next;
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
	node *curr = *head;
	node *new_item;
	
	if (!head || !item_name) return EXIT_FAILURE;
	
	if (pos == 0) {
		new_item = malloc(sizeof(node));
		if (!new_item) return EXIT_FAILURE;
		
		new_item->item_name = item_name;
		new_item->price = price;
		new_item->quantity = quantity;
		new_item->next = NULL;
		
		*head = new_item;
		
		return EXIT_SUCCESS;
	}
	
	int i = 0;
	while (curr) {
		if (i == pos-1) {
			new_item = malloc(sizeof(node));
			if (!new_item) return EXIT_FAILURE;
			
			new_item->item_name = item_name;
			new_item->price = price;
			new_item->quantity = quantity;
			new_item->next = curr->next;
			
			curr->next = new_item;
			
			return EXIT_SUCCESS;
		}
		
		curr = curr->next;
		i++;
	}
	
	return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	node *curr = *head;
	node *next = curr->next;
	
	int i = 0;
	while (curr && curr->item_name) {
		if (i == pos-1) {
			curr->item_name = item_name;
			curr->price = price;
			curr->quantity = quantity;
			return EXIT_SUCCESS;
		}
		
		curr = next;
		next = curr->next;
		
		i++;
	}
	
	return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	node *curr = *head;
	node *next = curr->next;
	
	int i = 0;
	while (curr && curr->item_name) {
		if (i == pos-1) {
			curr->next = next->next;
			free(next);
			return EXIT_SUCCESS;
		}
		
		curr = next;
		next = curr->next;
		
		i++;
	}
	
	return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	node *curr = *head;
	node *next = curr->next;
	node *swap_1 = NULL;
	node *swap_2 = NULL;
	
	int i = 0;
	while (curr && curr->item_name) {
		if (i == pos1-1) {
			swap_1 = curr;
		}
		if (i == pos2-1) {
			swap_2 = curr;
		}
		
		curr = next;
		next = curr->next;
		
		i++;
	}
	
	node *temp = swap_1->next;
	swap_1->next = swap_2->next;
	swap_2->next = temp;
	
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	node *curr = head;
	node *next = curr->next;
	
	float highest_price = curr->price;
	int highest_price_pos = 0;
	
	int i = 0;
	while (curr && curr->item_name) {
		if (curr->price > highest_price) {
			highest_price = curr->price;
			highest_price_pos = i+1;
		}
		
		curr = next;
		next = curr->next;
		
		i++;
	}
	
	*pos = highest_price_pos;
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	node *curr = head;
	node *next = curr->next;
	float sum = 0;
	
	while (curr) {
		sum += curr->price * curr->quantity;
		curr = next;
		next = curr->next;
	}
	
	*total = sum;
	return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	node *curr = head;
	FILE *fptr = fopen(filename, "w");
	
	if (!fptr) return EXIT_FAILURE;
	
	if (curr) {
		fprintf(fptr, "%s,%f,%d\n", curr->item_name, curr->price, curr->quantity);
	}
	
	while (curr->next) {
		curr = curr->next;
		fprintf(fptr, "%s,%f,%d\n", curr->item_name, curr->price, curr->quantity);
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
	node *curr = *head;
	FILE *fptr = fopen(filename, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token, *saveptr;
	char *item_name, *price_string, *quantity_string;
	float price, quantity;
	
	if (!fptr) return EXIT_FAILURE;
	
	while ((read = getline(&line, &len, fptr)) != -1) {
		if (line[0] == '#') {
			// skip comments
			continue;
		}
		
		token = strtok_r(line, ",", &saveptr);
		item_name = token;
		token = strtok_r(NULL, ",", &saveptr);
		price_string = token;
		token = strtok_r(NULL, ",", &saveptr);
		quantity_string = token;
		
		price = atof(price_string);
		quantity = atoi(quantity_string);
		
		list_add_item_at_pos(head, item_name, price, quantity, 0);
	}
	
	fclose(fptr);
	free(line);
	
	return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	node *curr = *head;
	node *next = curr->next;
	node *next_next = next->next;
	int found = 0;
	
	while (curr->next) {
		if (curr->item_name == next->item_name) {
			curr->quantity += next->quantity;
			found = 1;
		}
		
		curr = next;
		next = next_next;
		if (next) next_next = next->next;
	}
	
	if (found) {
		*head = curr;
		list_remove_item_at_pos(head, 1);
	}
	
	return EXIT_SUCCESS;
}
