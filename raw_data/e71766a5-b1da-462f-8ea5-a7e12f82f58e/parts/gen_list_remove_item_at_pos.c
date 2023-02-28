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
int CURR_LEN=0;

// Note: All list_ functions should return a status code
// EXIT_FAILURE or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos>CURR_LEN) return EXIT_FAILURE;
    struct _node *curr = *head;
    for(int i=1;i<pos-1;i++){
        curr=curr->next;
    }
    curr->next = curr->next->next;
    // bug 2: missing check for next == NULL
    // bug 3: missing free of item
    // bug 4: missing free of item_name
    // bug 5: memory leak by failing to update *head
    // bug 6: missing check for *head == NULL (doesn't update CURR_LEN)
    return EXIT_SUCCESS;
}
