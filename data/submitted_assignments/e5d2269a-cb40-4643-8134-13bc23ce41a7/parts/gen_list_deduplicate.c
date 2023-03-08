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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    node* _head1 = *head;
    while(_head1 && _head1->next){
        node* _head2 = _head1->next;
        node* _prev = _head1;
        while(_head2){
            int to_free = 0;
            // bug 2: missing check for item_name == NULL
            if(!strcmp(_head1->item_name, _head2->item_name)){
                _head1->quantity += _head2->quantity;
                _prev->next = _head2->next;
                to_free = 1;
            }
            if(to_free){
                node* tmp = _head2;
                _head2 = _head2->next;
                // bug 3: missing free of item_name
                free(tmp);
            } else {
                _prev = _head2;
                _head2 = _head2->next;
            }
        }
        _head1 = _head1->next;
    }   
    return EXIT_SUCCESS;
}
