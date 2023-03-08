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
	node *new_node = malloc(sizeof(node));
	if (new_node == NULL) {
		return EXIT_FAILURE;
	}
	*head = new_node;
	new_node->next = NULL;
	return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	if (head == NULL) {
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
	node *cur_node = head;
	int i = 1;
	while (cur_node != NULL) {
		char str[MAX_ITEM_PRINT_LEN];
		if (list_item_to_string(cur_node, str) == EXIT_FAILURE) {
			return EXIT_FAILURE;
		}
		printf("%d: %s\n", i, str);
		cur_node = cur_node->next;
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
	node *new_node = malloc(sizeof(node));
	if (new_node == NULL) {
		return EXIT_FAILURE;
	}
	new_node->item_name = item_name;
	new_node->price = price;
	new_node->quantity = quantity;
	if (pos == 1) {
		new_node->next = *head;
		*head = new_node;
		return EXIT_SUCCESS;
	}
	node *prev_node = *head;
	node *cur_node = (*head)->next;
	unsigned int i = 2;
	while (cur_node != NULL) {
		if (i == pos) {
			new_node->next = cur_node;
			prev_node->next = new_node;
			return EXIT_SUCCESS;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
		i++;
	}
	if (i == pos) {
		prev_node->next = new_node;
		new_node->next = NULL;
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	if (pos == 1) {
		(*head)->item_name = item_name;
		(*head)->price = price;
		(*head)->quantity = quantity;
		return EXIT_SUCCESS;
	}
	node *cur_node = (*head)->next;
	unsigned int i = 2;
	while (cur_node != NULL) {
		if (i == pos) {
			cur_node->item_name = item_name;
			cur_node->price = price;
			cur_node->quantity = quantity;
			return EXIT_SUCCESS;
		}
		cur_node = cur_node->next;
		i++;
	}
	return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	if (pos == 1) {
		node *cur_node = *head;
		*head = (*head)->next;
		free(cur_node);
		return EXIT_SUCCESS;
	}
	node *prev_node = *head;
	node *cur_node = (*head)->next;
	unsigned int i = 2;
	while (cur_node != NULL) {
		if (i == pos) {
			prev_node->next = cur_node->next;
			free(cur_node);
			return EXIT_SUCCESS;
		}
		prev_node = cur_node;
		cur_node = cur_node->next;
		i++;
	}
	return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	node *node1 = *head;
	node *node2 = *head;
	unsigned int i = 1;
	while (node1 != NULL) {
		if (i == pos1) {
			break;
		}
		node1 = node1->next;
		i++;
	}
	i = 1;
	while (node2 != NULL) {
		if (i == pos2) {
			break;
		}
		node2 = node2->next;
		i++;
	}
	if (node1 == NULL || node2 == NULL) {
		return EXIT_FAILURE;
	}
	char *temp_item_name = node1->item_name;
	float temp_price = node1->price;
	int temp_quantity = node1->quantity;
	node1->item_name = node2->item_name;
	node1->price = node2->price;
	node1->quantity = node2->quantity;
	node2->item_name = temp_item_name;
	node2->price = temp_price;
	node2->quantity = temp_quantity;
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *cur_node = head;
	unsigned int i = 1;
	unsigned int max_pos = 1;
	float max_price = cur_node->price;
	while (cur_node != NULL) {
		if (cur_node->price > max_price) {
			max_price = cur_node->price;
			max_pos = i;
		}
		cur_node = cur_node->next;
		i++;
	}
	*pos = max_pos;
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	if (head == NULL) {
		return EXIT_FAILURE;
	}
	node *cur_node = head;
	float sum = 0;
	while (cur_node != NULL) {
		sum += cur_node->price * cur_node->quantity;
		cur_node = cur_node->next;
	}
	*total = sum;
	return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		return EXIT_FAILURE;
	}
	node *cur_node = head;
	while (cur_node != NULL) {
		fprintf(fp, "%s,%.2f,%d\n", cur_node->item_name, cur_node->price, cur_node->quantity);
		cur_node = cur_node->next;
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
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		return EXIT_FAILURE;
	}
	node *cur_node = *head;
	while (cur_node->next != NULL) {
		cur_node = cur_node->next;
	}
	char *item_name = NULL;
	float price;
	int quantity;
	while (fscanf(fp, "%m[^,],%f,%d\n", &item_name, &price, &quantity) != EOF) {
		cur_node->next = malloc(sizeof(node));
		cur_node->next->item_name = item_name;
		cur_node->next->price = price;
		cur_node->next->quantity = quantity;
		cur_node->next->next = NULL;
		cur_node = cur_node->next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	node *cur_node = *head;
	while (cur_node != NULL) {
		node *cur_node2 = cur_node->next;
		node *prev_node2 = cur_node;
		while (cur_node2 != NULL) {
			if (strcmp(cur_node->item_name, cur_node2->item_name) == 0) {
				cur_node->quantity += cur_node2->quantity;
				prev_node2->next = cur_node2->next;
				free(cur_node2);
				cur_node2 = prev_node2;
			}
			prev_node2 = cur_node2;
			cur_node2 = cur_node2->next;
		}
		cur_node = cur_node->next;
	}
	return EXIT_SUCCESS;
}
