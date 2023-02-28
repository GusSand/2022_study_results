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
// update the item at position pos
int list_update_item_at_pos(node **head, char *item_name, float price, int quantity, unsigned int pos) {
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL
    if(*head == NULL){
        return EXIT_FAILURE;
    }
    int currPos = 0;
    while(*head != NULL){
        if(currPos == pos){
            // bug 2: buffer overflow updating item_name
            strcpy((*head)->item_name, item_name);
            (*head)->price = price;
            (*head)->quantity = quantity;
            return EXIT_SUCCESS;
        }
        currPos++;
        // bug 3: memory leak updating head pointer
        *head = (*head)->next;
    }
    return EXIT_FAILURE;
}
