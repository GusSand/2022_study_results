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
// find the item position with the highest single price
int list_find_highest_price_item_position(node *head, int *pos) 
{
    // TODO: Implement this function, 
    // bug 2: int vs float confusion
    int max = -10000;
    int max_ind;
    // bug 1: failed to initialize cur
    node* cur;
    cur->next = head;
    int i = 0;
    while (1){       
        if (cur == NULL){
            break;
        }
        if (cur->price >= max){
            max = cur->price;
            max_ind = i;
        }
        i++;
        cur = cur->next;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
