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
    if(pos1==pos2)
        return EXIT_SUCCESS;

    // bug 1: missing check for head == NULL
    node *prev1 = NULL, *curr1 = *head;
    int i = 1;
    while(curr1 && i!=pos1) {
        prev1 = curr1;
        curr1 = curr1->next;
        i++;
    }
    node *prev2 = NULL, *curr2 = *head;
    i = 1;
    while(curr2 && i!=pos2) {
        prev2 = curr2;
        curr2 = curr2->next;
        i++;
    }
    if(curr1 == NULL || curr2 ==NULL) {
        return EXIT_SUCCESS;
    }
    if(prev1 != NULL) {
        prev1->next = curr2;
    }
    else{
        *head = curr2;}
    if(prev2 != NULL) {
        prev2->next = curr1;
    }
    else{
        *head = curr1;}
    node* temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
    

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
