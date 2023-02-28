#include <stdio.h> 
#include <stdlib.h>
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
    // bug 1: missing check for head == NULL
    // bug 2: sizeof on pointer
    // bug 3: type confusion using linked list as array
    if (*head == NULL || pos1 == pos2 || pos1 > sizeof(*head) || pos2 > sizeof(*head))
    {
        return EXIT_FAILURE;
    }
    
    node *item_to_swap1;
    node *item_to_swap2;
    node *temp;
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos1){
            item_to_swap1 = *head;
        }
        else if(currPos == pos2){
            item_to_swap2 = *head;
        }
        currPos++;
        *head = (*head)->next;
        // bug 4: memory leak by overwriting head pointer
    }
    temp = item_to_swap1;
    item_to_swap1 = item_to_swap2;
    item_to_swap2 = temp;
    return EXIT_SUCCESS;
}
