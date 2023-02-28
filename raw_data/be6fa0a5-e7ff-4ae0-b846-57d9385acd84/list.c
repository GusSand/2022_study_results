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

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was 
// successful or not.

// create a new list
int list_init(node **head)
{
    *head = NULL;
    return EXIT_SUCCESS;
}

// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    if (head == NULL) {
        return EXIT_SUCCESS;
    }

    sprintf(str, "%d * %s @ %.2f ea", head->quantity, head->item_name, head->price);

    return EXIT_SUCCESS;
}

// print the entire list to an externally allocated string
// This should be in the format of:
// "item_name item_name item_name ...", where item_name is a string
int list_to_string(node *head) {
    if (head == NULL) {
        return EXIT_SUCCESS;
    }

    while(head != NULL) {
        printf("%s", head->item_name);
        head = head->next;
        if(head != NULL) {
            printf(" ");
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
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    unsigned int pos = 1;
    while(head != NULL) {
        printf("%d: %d * %s @ %.2f ea\n", pos, head->quantity, head->item_name, head->price);
        head = head->next;
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
int list_add_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos)
{
    unsigned int i = 1;
    node *prev = NULL;
    node *curr = *head;

    if(pos == 0)
        return EXIT_FAILURE;
    

    while(curr != NULL) {
        if(i == pos) {
            node newItem;
            newItem.item_name = item_name;
            newItem.price = price;
            newItem.quantity = quantity;
            newItem.next = curr;

            if(prev == NULL) {
                *head = &newItem;
            } else {
                prev->next = &newItem;
            }

            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }

    return EXIT_FAILURE;
}

// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    unsigned int i = 1;
    node *prev = NULL;
    node *curr = *head;

    if(pos == 0)
        return EXIT_FAILURE;

    while(curr != NULL) {
        if(i == pos) {
            curr->item_name = item_name;
            curr->price = price;
            curr->quantity = quantity;

            return EXIT_SUCCESS;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }

    return EXIT_FAILURE;
}

// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos) {
    int i = 1;
    node *prev = NULL;
    node *curr = *head;

    if(pos == 0)
        return EXIT_FAILURE;

    while(curr != NULL) {
        if(i == pos) {
            // If prev is NULL, we are removing the head
            if(prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }

            return EXIT_SUCCESS;
        }

        prev = curr;
        curr = curr->next;
        i++;
    }
    
    return EXIT_FAILURE;
}

// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    node *prev1 = NULL;
    node *curr1 = *head;

    int i = 1;
    while(curr1 != NULL) {
        if(i == pos1) {
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
    }

    node *prev2 = NULL;
    node *curr2 = *head;

    i = 1;
    while(curr2 != NULL) {
        if(i == pos2) {
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if(prev1 == NULL) {
        *head = curr2;
    } else {
        prev1->next = curr2;
    }

    if(prev2 == NULL) {
        *head = curr1;
    } else {
        prev2->next = curr1;
    }

    if(curr1->next == curr2) {
        curr1->next = curr2->next;
        curr2->next = curr1;
    } else if(curr2->next == curr1) {
        curr2->next = curr1->next;
        curr1->next = curr2;
    }

    return EXIT_SUCCESS;
}

// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    int highestPrice = 0;
    int highestPricePos = 0;
    unsigned int i = 1;

    while(head != NULL) {
        if(head->price > highestPrice) {
            highestPrice = head->price;
            highestPricePos = i;
        }
        head = head->next;
        i++;
    }

    *pos = highestPricePos;

    return EXIT_SUCCESS;
}

// calculate the total cost of the list (sum of all prices * quantities)
int list_cost_sum(node *head, float *total)
{
    if(head == NULL) {
        return EXIT_FAILURE;
    }

    *total = 0;
    while(head != NULL) {
        *total += (head->quantity * head->price);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    FILE *f = fopen(filename, "w");
    if(f == NULL) {
        return EXIT_FAILURE;
    }

    while(head != NULL) {
        fprintf(f, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);

        head = head->next;
    }
    
}

// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        return EXIT_FAILURE;
    }

    
}

// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    return EXIT_SUCCESS;
}

