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
    int i = 0;
    int j =0;
    // bug 1: type confusion head vs *head
    node *n1 = head;
    node *n2 = head;
    node *n1prev = head;
    node *n2prev = head;
    node *temp;
    if(pos1 == pos2){
        return EXIT_SUCCESS;
    }
    if(pos1 <0 || pos2 <0){
        return EXIT_FAILURE;
    }
    while (i != pos1){
        i++;
        n1prev = n1;
        // bug 2: missing check for next == NULL
        n1 = n1->next;
    }
    while (j != pos2){
        j++;
        n2prev = n2;
        // bug 3: missing check for next == NULL
        n2 = n2->next;
    }
    // bug 4: missing check for next == NULL
    n1prev->next = n2;
    n2prev->next = n1;
    temp  = n2->next;
    n2->next = n1->next;
    n1->next = temp;

    return EXIT_SUCCESS;
}
