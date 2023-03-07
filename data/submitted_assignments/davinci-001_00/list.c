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
	if (*head == NULL) {
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
		strcpy(str, "empty list");
		return EXIT_SUCCESS;
	}
	node *current = head->next;
	char *name = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	char *price = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	char *quantity = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	int i = 0;
	if (!name || !price || !quantity) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	while (current != NULL) {
		sprintf(name, "%s", current->item_name);
		sprintf(price, "%.2f", current->price);
		sprintf(quantity, "%d", current->quantity);
		char *toPrint = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		if (!toPrint) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		strcat(toPrint, quantity);
		strcat(toPrint, " * ");
		strcat(toPrint, name);
		strcat(toPrint, " @ $");
		strcat(toPrint, price);
		strcat(toPrint, " ea");
		strcpy(str + i, toPrint);
		i += strlen(toPrint);
		strcat(str, "\n");
		free(toPrint);
		current = current->next;
	}
	free(name);
	free(price);
	free(quantity);
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
		printf("empty list\n");
		return EXIT_SUCCESS;
	}
	node *current = head->next;
	char *str = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	int i = 0;
	if (!str) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	while (current != NULL) {
		char *name = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		char *price = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		char *quantity = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		if (!name || !price || !quantity) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		sprintf(name, "%s", current->item_name);
		sprintf(price, "%.2f", current->price);
		sprintf(quantity, "%d", current->quantity);
		char *toPrint = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
		if (!toPrint) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		strcat(toPrint, quantity);
		strcat(toPrint, " * ");
		strcat(toPrint, name);
		strcat(toPrint, " @ $");
		strcat(toPrint, price);
		strcat(toPrint, " ea");
		strcat(str, toPrint);
		strcat(str, "\n");
		free(toPrint);
		current = current->next;
	}
	printf("%s", str);
	free(str);
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
	if (*head == NULL) {
		list_init(head);
	}
	node *current = *head;
	unsigned int i = 0;
	while (current != NULL) {
		if (i == pos - 1) {
			node *new = malloc(sizeof(node));
			if (!new) {
				fprintf(stderr, "Not enough memory!");
				return EXIT_FAILURE;
			}
			new->item_name = malloc(sizeof(char) * strlen(item_name));
			if (!new->item_name) {
				fprintf(stderr, "Not enough memory!");
				return EXIT_FAILURE;
			}
			strcpy(new->item_name, item_name);
			new->price = price;
			new->quantity = quantity;
			new->next = current->next;
			current->next = new;
			break;
		}
		current = current->next;
		i++;
	}
	return EXIT_SUCCESS;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
	if (*head == NULL) {
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	node *current = *head;
	unsigned int i = 0;
	while (current != NULL) {
		if (i == pos - 1) {
			current->item_name = malloc(sizeof(char) * strlen(item_name));
			strcpy(current->item_name, item_name);
			current->price = price;
			current->quantity = quantity;
			break;
		}
		current = current->next;
		i++;
	}
	return EXIT_SUCCESS;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
	if (*head == NULL) {
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	node *current = *head;
	unsigned int i = 0;
	while (current != NULL) {
		if (i == pos - 1) {
			node *next = current->next;
			free(current);
			current = next;
			break;
		}
		current = current->next;
		i++;
	}
	return EXIT_SUCCESS;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
	if (*head == NULL) {
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	node *current = *head;
	node *pos1_node = NULL;
	node *pos2_node = NULL;
	unsigned int i = 0;
	while (current != NULL) {
		if (i == pos1 - 1) {
			pos1_node = current;
		}
		if (i == pos2 - 1) {
			pos2_node = current;
		}
		current = current->next;
		i++;
	}
	if (pos1_node == NULL || pos2_node == NULL) {
		fprintf(stderr, "No such positions!");
		return EXIT_FAILURE;
	}
	node *temp = pos1_node->next;
	pos1_node->next = pos2_node->next;
	pos2_node->next = temp;
	if (pos1 == 1) {
		*head = pos2_node;
	} else if (pos2 == 1) {
		*head = pos1_node;
	}
	return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) {
	if (head == NULL) {
		fprintf(stderr, "empty list");
		return EXIT_FAILURE;
	}
	node *current = head->next;
	node *max = current;
	int i = 0;
	while (current != NULL) {
		if (current->price > max->price) {
			max = current;
		}
		current = current->next;
		i++;
	}
	*pos = i;
	return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total) {
	if (head == NULL) {
		fprintf(stderr, "empty list");
		return EXIT_FAILURE;
	}
	node *current = head->next;
	float sum = 0.0;
	while (current != NULL) {
		sum += current->price * current->quantity;
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
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	FILE *file = fopen(filename, "w");
	if (!file) {
		fprintf(stderr, "Couldn't open file!");
		return EXIT_FAILURE;
	}
	char *str = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	if (!str) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	node *current = head->next;
	while (current != NULL) {
		sprintf(str, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
		fputs(str, file);
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
	if (*head == NULL) {
		list_init(head);
	}
	node *current = *head;
	FILE *file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "Couldn't open file!");
		return EXIT_FAILURE;
	}
	char *line = malloc(sizeof(char) * MAX_ITEM_PRINT_LEN);
	if (!line) {
		fprintf(stderr, "Not enough memory!");
		return EXIT_FAILURE;
	}
	while (fgets(line, MAX_ITEM_PRINT_LEN, file) != NULL) {
		node *new = malloc(sizeof(node));
		if (!new) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		char *token[3];
		int i = 0;
		char *next = line;
		while (next[i] != '\n') {
			token[i] = next;
			i++;
			next = next + 1;
		}
		token[i] = next;
		i++;
		new->item_name = malloc(sizeof(char) * (strlen(token[0]) - 1));
		if (!new->item_name) {
			fprintf(stderr, "Not enough memory!");
			return EXIT_FAILURE;
		}
		strcpy(new->item_name, token[0]);
		new->price = strtod(token[1], NULL);
		new->quantity = atoi(token[2]);
		new->next = NULL;
		current->next = new;
		current = new;
	}
	fclose(file);
	return EXIT_SUCCESS;
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
	if (*head == NULL) {
		fprintf(stderr, "Empty list!");
		return EXIT_FAILURE;
	}
	node *current = *head;
	node *next = current->next;
	node *toFree = current;
	while (next!= NULL) {
		node *current2 = next->next;
		while (current2!= NULL) {
			if (!strcmp(current->item_name, current2->item_name)) {
				current->quantity += current2->quantity;
				current->price += current2->price;
				current2 = current2->next;
				toFree = toFree->next;
				free(toFree);
			} else {
				current = current->next;
			}
		}
		next = next->next;
	}
	*head = current;
	return EXIT_SUCCESS;
}
