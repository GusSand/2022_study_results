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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// allocate memory for node
	*head = malloc(sizeof(node));
	
	// check if malloc failed
	if(*head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set members to NULL
	(*head)->item_name = NULL;
	(*head)->price = 0.0;
	(*head)->quantity = 0;
	(*head)->next = NULL;
	
	// return success
	return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if str is NULL
	if(str == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if item_name is NULL
	if(head->item_name == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if str is of sufficient length
	if(strlen(head->item_name) + (int)((head->price*100.0) + .5) + 20 > MAX_ITEM_PRINT_LEN) {
		return EXIT_FAILURE;
	}
	
	// create string
	sprintf(str, "%d * %s @ $%0.2f ea", head->quantity, head->item_name, head->price);
	
	// return success
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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if item_name is NULL
	if(head->item_name == NULL) {
		return EXIT_FAILURE;
	}
	
	// print first node
	printf("%d: %d * %s @ $%0.2f ea\n", 1, head->quantity, head->item_name, head->price);
	
	// print rest of nodes
	node *temp_node = head->next;
	int pos = 2;
	while(temp_node != NULL) {
		// check if item_name is NULL
		if(temp_node->item_name == NULL) {
			return EXIT_FAILURE;
		}
		
		// print node
		printf("%d: %d * %s @ $%0.2f ea\n", pos, temp_node->quantity, temp_node->item_name, temp_node->price);
		
		// move to next node
		temp_node = temp_node->next;
		pos++;
	}
	
	// return success
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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if item_name is NULL
	if(item_name == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up new node
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL) {
		return EXIT_FAILURE;
	}
	new_node->item_name = strdup(item_name);
	new_node->price = price;
	new_node->quantity = quantity;
	new_node->next = NULL;
	
	// check if pos is 0
	if(pos == 0) {
		new_node->next = *head;
		*head = new_node;
		return EXIT_SUCCESS;
	}
	
	// set up temp node
	node *temp_node = *head;
	int i = 1;
	
	// traverse to pos
	while(i < pos) {
		if(temp_node->next == NULL) {
			free(new_node);
			return EXIT_FAILURE;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// set new node's next to temp node's next
	new_node->next = temp_node->next;
	
	// set temp node's next to new node
	temp_node->next = new_node;
	
	// return success
	return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if item_name is NULL
	if(item_name == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if pos is 0
	if(pos == 0) {
		*head = malloc(sizeof(node));
		(*head)->item_name = strdup(item_name);
		(*head)->price = price;
		(*head)->quantity = quantity;
		(*head)->next = NULL;
		return EXIT_SUCCESS;
	}
	
	// set up temp node
	node *temp_node = *head;
	int i = 1;
	
	// traverse to pos
	while(i < pos) {
		if(temp_node->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// set temp node's item_name to item_name
	temp_node->item_name = strdup(item_name);
	
	// set temp node's price to price
	temp_node->price = price;
	
	// set temp node's quantity to quantity
	temp_node->quantity = quantity;
	
	// return success
	return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// check if pos is 0
	if(pos == 0) {
		if((*head)->next == NULL) {
			free(*head);
			*head = NULL;
			return EXIT_SUCCESS;
		}
		
		node *temp_node = (*head)->next;
		free(*head);
		*head = temp_node;
		return EXIT_SUCCESS;
	}
	
	// set up temp node
	node *temp_node = *head;
	int i = 1;
	
	// traverse to pos
	while(i < pos) {
		if(temp_node->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// check if next node is NULL
	if(temp_node->next == NULL) {
		return EXIT_FAILURE;
	}
	
	// set temp node's next to next node's next
	temp_node->next = temp_node->next->next;
	
	// return success
	return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = (*head);
	int i = 0;
	
	// traverse to pos1
	while(i < pos1) {
		if(temp_node->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// set up temp node2
	node *temp_node2 = (*head);
	i = 0;
	
	// traverse to pos2
	while(i < pos2) {
		if(temp_node2->next == NULL) {
			return EXIT_FAILURE;
		}
		temp_node2 = temp_node2->next;
		i++;
	}
	
	// swap temp node and temp node2
	node *temp_node3 = temp_node->next;
	temp_node->next = temp_node2->next;
	temp_node2->next = temp_node3;
	
	// return success
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = head;
	int i = 0;
	float highest = 0;
	
	// traverse to end of list
	while(temp_node != NULL) {
		if(temp_node->price > highest) {
			highest = temp_node->price;
			*pos = i;
		}
		temp_node = temp_node->next;
		i++;
	}
	
	// return success
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = head;
	int i = 0;
	float sum = 0;
	
	// traverse to end of list
	while(temp_node!= NULL) {
		sum += ((temp_node->price) * (temp_node->quantity));
		temp_node = temp_node->next;
		i++;
	}
	
	// set total to sum
	*total = sum;
	
	// return success
	return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = head;
	
	// open file
	FILE *f = fopen(filename, "w");
	
	// check if file is NULL
	if(f == NULL) {
		return EXIT_FAILURE;
	}
	
	// write to file
	while(temp_node != NULL) {
		fprintf(f, "%s,%f,%d\n", temp_node->item_name, temp_node->price, temp_node->quantity);
		temp_node = temp_node->next;
	}
	
	// close file
	fclose(f);
	
	// return success
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
	// check if head is NULL
	if(head == NULL) {
		return EXIT_FAILURE;
	}
	
	// set up temp node
	node *temp_node = *head;
	
	// traverse list
	while(temp_node->next != NULL) {
		if(strcmp(temp_node->item_name, temp_node->next->item_name) == 0) {
			temp_node->quantity += temp_node->next->quantity;
			node *temp_node2 = temp_node->next;
			temp_node->next = temp_node->next->next;
			free(temp_node2);
		}
		else {
			temp_node = temp_node->next;
		}
	}
	
	// return success
	return EXIT_SUCCESS;
}
