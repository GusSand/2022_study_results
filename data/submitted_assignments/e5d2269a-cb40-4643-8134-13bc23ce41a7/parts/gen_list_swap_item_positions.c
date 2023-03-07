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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int i = 1;

    // bug 1: missing check for head == NULL
    node* _head1 = *head;
    node* _prev1 = NULL;
    int small_pos = pos1 < pos2 ? pos1 : pos2;
    int large_pos = pos1 > pos2 ? pos1 : pos2;

    // bug 2: missing check for head* == NULL
    while(_head1->next && i < small_pos){
        i++;
        _prev1 = _head1;
        _head1 = _head1->next;
    }

    i = 1;
    node* _head2 = *head;
    node* _prev2 = NULL;
    // bug 3: missing check for head* == NULL
    while(_head2->next && i < large_pos){
        i++;
        _prev2 = _head2;
        _head2 = _head2->next;
    }

    // bug 4: missing check for cursor == NULL
    _prev2->next = _head1;
    node* tmp = _head1->next;
    _head1->next = _head2->next;
    _head2->next = tmp;
    if(_prev1){
        _prev1->next = _head2;
    }
    if(small_pos==1)
        *head = _head2;
    return EXIT_SUCCESS;    
}
