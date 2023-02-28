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
    // bug 1: missing check for head == NULL
    // bug 2: type confusion, mixing up char* and char
    struct _node node1 = {*item_name,price, quantity, NULL};
    
    // if (head[pos] == NULL){
    //     return EXIT_FAILURE;
    // }
    // bug 3: type confusion, using linked list as array
    // bug 4: returning reference to stack variable
    head[pos] = &node1;
    //head[pos]->next = NULL;
    // if (pos != 0){
    //     head[pos - 1]->next = head[pos];
    // }
    return EXIT_SUCCESS;
}
