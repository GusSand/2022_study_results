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

#include "reflist.h"
// insert a new item before the specified position
// (1 = first item, 2 = second item, etc)
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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    if(pos == 1){
        node *new_node = malloc(sizeof(node));
        new_node->item_name = item_name; // bug 1: missing strdup
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = current;
        *head = new_node;
    }else{
        int i;
        for (i = 1; i < (pos - 1); i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        node *new_node = malloc(sizeof(node));
        new_node->item_name = item_name; // bug 2: missing strdup
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = current->next;
        current->next = new_node;
    }
    return EXIT_SUCCESS;

}
