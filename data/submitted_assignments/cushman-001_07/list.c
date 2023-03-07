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
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	*head = NULL;
	return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	if(head == NULL || str == NULL) {
		return EXIT_FAILURE;
	}

	if(head->quantity == 0) {
		strcpy(str, "");
	}
	else {
		sprintf(str, "%d * %s @ $%.2f ea", 
							head->quantity, 
							head->item_name, 
							head->price);
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
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = head;
	int pos = 1;
	while(temp != NULL) {
		char str[MAX_ITEM_PRINT_LEN];
		list_item_to_string(temp, str);
		printf("%d: %s\n", pos, str);
		
		temp = temp->next;
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
	if(head == NULL || item_name == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = *head;
	node *new_node = malloc(sizeof(node));

	if(new_node == NULL) {
		return EXIT_FAILURE;
	}

	new_node->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
	if(new_node->item_name == NULL) {
		free(new_node);
		return EXIT_FAILURE;
	}

	strcpy(new_node->item_name, item_name);
	new_node->price = price;
	new_node->quantity = quantity;
	new_node->next = NULL;

	// check if pos is valid
	if(pos == 0) {
		return EXIT_FAILURE;
	}

	if(pos == 1) {
		if(*head == NULL) {
			*head = new_node;
		}
		else {
			new_node->next = temp;
			*head = new_node;
		}
		return EXIT_SUCCESS;
	}

	int index = 1;
	while(temp->next != NULL && index < pos - 1) {
		temp = temp->next;
		index++;
	}

	if(index == pos - 1) {
		new_node->next = temp->next;
		temp->next = new_node;
		return EXIT_SUCCESS;
	}
	else {
		return EXIT_FAILURE;
	}	
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	if(head == NULL || item_name == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = *head;
	if(pos == 0) {
		return EXIT_FAILURE;
	}

	int index = 1;
	while(temp->next != NULL && index < pos - 1) {
		temp = temp->next;
		index++;
	}

	if(index == pos - 1) {
		if(temp->next == NULL) {
			return EXIT_FAILURE;
		}
		else {
			if(temp->next->item_name != NULL) {
				free(temp->next->item_name);
			}
			temp->next->item_name = malloc(sizeof(char) * (strlen(item_name) + 1));
			temp->next->price = price;
			temp->next->quantity = quantity;
			return EXIT_SUCCESS;
		}
	}
	else {
		return EXIT_FAILURE;
	}
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	if(pos == 0) {
		return EXIT_FAILURE;
	}

	node *temp = *head;
	if(pos == 1) {
		if(*head == NULL) {
			return EXIT_FAILURE;
		}
		else {
			*head = temp->next;
			free(temp->item_name);
			free(temp);
			return EXIT_SUCCESS;
		}
	}

	int index = 1;
	while(temp->next!= NULL && index < pos - 1) {
		temp = temp->next;
		index++;
	}

	if(index == pos - 1) {
		if(temp->next == NULL) {
			return EXIT_FAILURE;
		}
		else {
			node *temp2 = temp->next;
			temp->next = temp->next->next;
			free(temp2->item_name);
			free(temp2);
			return EXIT_SUCCESS;
		}
	}
	else {
		return EXIT_FAILURE;
	}
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	if(pos1 == 0 || pos2 == 0) {
		return EXIT_FAILURE;
	}
	
	node *temp = *head;
	if(pos1 == pos2) {
		return EXIT_SUCCESS;
	}

	int index = 1;
	while(temp->next!= NULL && index < pos1 - 1) {
		temp = temp->next;
		index++;
	}

	if(index == pos1 - 1) {
		if(temp->next == NULL) {
			return EXIT_FAILURE;
		}
		else {
			node *temp1 = temp->next;
			node *temp2 = temp1->next;
			temp->next = temp2;
			temp1->next = temp2->next;
			temp2->next = temp1;
			return EXIT_SUCCESS;
		}
	}
	else {
		return EXIT_FAILURE;
	}
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	if(head == NULL || pos == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = head;
	float highest_price = 0;
	int index = 0;
	while(temp != NULL) {
		if(highest_price < temp->price) {
			highest_price = temp->price;
			index = temp->quantity;
		}
		temp = temp->next;
	}

	*pos = index;
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	if(head == NULL || total == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = head;
	float sum = 0;
	while(temp!= NULL) {
		sum += temp->price * temp->quantity;
		temp = temp->next;
	}

	*total = sum;
	return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	if(head == NULL || filename == NULL) {
		return EXIT_FAILURE;
	}

	FILE *fptr = fopen(filename, "w");
	if(fptr == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = head;
	while(temp!= NULL) {
		fprintf(fptr, "%s,%f,%d\n", temp->item_name, temp->price, temp->quantity);
		temp = temp->next;
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	if(head == NULL) {
		return EXIT_FAILURE;
	}

	node *temp = *head;
	node *head2 = NULL;
	node *temp2 = NULL;

	while(temp!= NULL) {
		temp2 = head2;
		head2 = malloc(sizeof(node));
		if(head2 == NULL) {
			return EXIT_FAILURE;
		}
		head2->item_name = malloc(sizeof(char) * (strlen(temp->item_name) + 1));
		strcpy(head2->item_name, temp->item_name);
		head2->price = temp->price;
		head2->quantity = temp->quantity;
		head2->next = NULL;
		if(temp2 != NULL) {
			temp2->next = head2;
		}

		temp = temp->next;
	}

	free(temp);
	*head = head2;
	return EXIT_SUCCESS;
}
