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
    // bug 1: type confusion on head vs *head
    node *ptr = head;
    int i = 0;
    if(pos < 0){
        return EXIT_FAILURE;
    }
    // bug 2: missing check for next == NULL
    // bug 3: missing check for *head == NULL
    // bug 4: missing check for head == NULL
    while(i != pos){
        i++;
        ptr = ptr->next;
    }
    ptr->quantity = quantity;
    // bug 5: missing free
    // bug 6: missing strdup
    ptr->item_name = item_name;
    ptr->price = price;
    return EXIT_SUCCESS;
}
