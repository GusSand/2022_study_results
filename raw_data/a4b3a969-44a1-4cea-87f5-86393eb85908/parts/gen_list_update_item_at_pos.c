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
    if(head == NULL || pos == 0){
        return EXIT_FAILURE;
    }
    node *current = *head;
    // bug 1: missing check for *head == NULL
    if(pos == 1){
        // bug 2: missing free
        // bug 3: missing strdup
        current->item_name = item_name;
        current->price = price;
        current->quantity = quantity;
    }else{
        int i;
        for (i = 1; i < pos; i++){
            if(current->next == NULL){
                break;
            }
            current = current->next;
        }
        // bug 4: missing free
        // bug 5: missing strdup
        current->item_name = item_name;
        current->price = price;
        current->quantity = quantity;
    }
    return EXIT_SUCCESS;
}
