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
    // bug 1: missing check for head == NULL
    if (*head == NULL){
        return EXIT_FAILURE;
    }
    if (pos1 > pos2){
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    node *curr1 = *head;
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    }
    int pos_count=1;
    node *curr2 = *head;
    while(pos_count < pos1){
        if (curr1 == NULL){
            return EXIT_FAILURE;
        }
        curr1=curr1->next;
        curr2=curr2->next;
        pos_count++;
    }
    while(pos_count < pos2){
        if (curr2 == NULL){
            return EXIT_FAILURE;
        }
        curr2=curr2->next;
        pos_count++;
    }
    node *temp = curr1->item_name;
    curr1->item_name = curr2->item_name;
    curr2->item_name = temp;
    int tempval = curr1->quantity;
    curr1->quantity = curr2->quantity;
    curr2->quantity = tempval;
    float tempfloat=curr1->price;
    curr1->price = curr2->price;
    curr2->price = tempfloat;
    return EXIT_SUCCESS;
}
