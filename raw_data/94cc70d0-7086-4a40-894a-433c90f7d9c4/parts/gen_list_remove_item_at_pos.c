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
//  or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"
// remove the item at position pos
int list_remove_item_at_pos(node **head, int pos)
{    
    // bug 1: missing check for head == NULL
    node* current = *head;
    int current_pos = 1;
    if(pos == 1){
        free(*head);
        // bug 2: memory leak by overwriting head pointer
        // bug 3: missing free of item_name

        *head = NULL;
        return EXIT_SUCCESS; 
    }
    while(current_pos < pos - 1){
        // bug 4: missing check for *head == NULL
        current = current->next;
        if(current->next == NULL)
            return EXIT_FAILURE;
        current_pos++;
    }
    node* before = current;
    node* to_remove = current->next;
    node* after = to_remove->next;

    before->next = after;
    free(to_remove);
    // bug 5: missing free of item_name
    return EXIT_SUCCESS;
}
