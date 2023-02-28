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
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    // bug 2: type confusion, *head vs head
    node *ptr = head;
    int i = 0;
    if(pos < 0){
        return EXIT_FAILURE;
    }
    while(i != pos-1){
        i++;
        ptr = ptr->next;
        // bug 3: missing check for next == NULL
    }
    ptr->next = ptr->next->next;
    // bug 4: missing free of item
    // bug 5: missing free of item_name
    return EXIT_SUCCESS;
}
