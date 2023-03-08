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
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // TODO: Implement this 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    if (pos1 == pos2){
        return EXIT_SUCCESS;
    }
    node *curr1 = *head;
    node *curr2 = *head;
    node *prev1 = NULL;
    node *prev2 = NULL;
    while(curr1 != NULL && curr2 != NULL){
        if (pos1 == 1){
            break;
        }
        prev1 = curr1;
        curr1 = curr1->next;
        if (pos2 == 1){
            break;
        }
        prev2 = curr2;
        curr2 = curr2->next;
        pos1--;
        pos2--;
    }
    if (curr1 == NULL || curr2 == NULL){
        return EXIT_FAILURE;
    }
    if (prev1 != NULL){
        prev1->next = curr2;
    }
    else{
        *head = curr2;
    }
    if (prev2 != NULL){
        prev2->next = curr1;
    }
    else{
        *head = curr1;
    }
    node *tmp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = tmp;
    return EXIT_SUCCESS;
}
