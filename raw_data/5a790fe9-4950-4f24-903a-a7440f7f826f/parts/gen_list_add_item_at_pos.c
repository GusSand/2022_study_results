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
    // bug 1: type confusion, head should be *head
    // bug 2: missing NULL check on head
    node *ptr = head;
    if (pos < 1){
        return EXIT_FAILURE;
    }
    if (pos == 1){
        // bug 3: failure to initialize newnode
        node *newnode;
        // bug 9: missing strdup
        newnode->item_name = item_name;
        newnode->price = price;
        newnode->quantity = quantity;
        // bug 5: memory leak
        newnode->next = ptr->next;
        // bug 6: type confusion, should be *head
        head = newnode;
    }
    if(pos != 1){
        // bug 8: missing check for next == NULL
        while(pos-- != 0) {
            if (pos == 1){
                // bug 4: failure to initialize newnode
                node *newnode;
                // bug 10: missing strdup
                newnode->item_name = item_name;
                newnode->price = price;
                newnode->quantity = quantity;
                newnode->next = ptr->next;
                ptr->next = newnode;
                break;
            }
            // bug 7: type confusion, should be *head
            head = ptr->next;
        }
        if(pos != 1){
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
