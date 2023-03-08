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
    // bug 1: missing check for head == NULL
    int mind, maxd;
    if (pos1<=pos2){mind = pos1; maxd = pos2;}
    else {mind = pos2; maxd = pos1;}

    node* min = *head;
    node* max = *head;
    node* temp = *head;
    int i=1;

    while (temp != NULL){        
        if(i==mind){
            max = temp;
            for (int j=i; j<maxd; j++){
                // bug 2: missing check for next == NULL
                max = max->next;}
            temp = min;
            min->next = max->next;
            max->next = temp->next;          
        }
        i++;
        temp = temp->next;
    }
    // bug 3: memory leak failing to update *head
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
