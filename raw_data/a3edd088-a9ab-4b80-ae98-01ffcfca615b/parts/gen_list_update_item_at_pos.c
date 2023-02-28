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
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    unsigned curr_pos = 0; // Initialize the current position to 0 
    // bug 1: type confusion head vs *head
    // bug 2: missing check for head == NULL
    // bug 3: missing check for *head == NULL
    // bug 4: missing check for next == NULL
    node* curr_node = head; 
    while (curr_pos != pos){
        if (curr_pos == pos){
            // bug 5: missing free
            // bug 6: missing strdup
            curr_node->item_name = item_name;
            curr_node->price = price;
            curr_node->quantity = quantity;
        }
        curr_pos++;
        curr_node = curr_node->next; 
    }
    return EXIT_SUCCESS;
}
