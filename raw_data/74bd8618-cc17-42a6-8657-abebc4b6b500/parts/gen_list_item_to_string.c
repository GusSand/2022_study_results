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
// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // create a string representation of the node head.
    // Since only a single item is being printed, the string should be
    // formatted exactly as shown in the sample output for list_item_to_string
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    if (head == NULL) {
        str = "";
        return EXIT_FAILURE;
    }
    int quantity = head->quantity;
    char item_name[MAX_ITEM_PRINT_LEN];
    // bug 4: does not ensure temporary string buffer is null-terminated
    strncpy(item_name, head->item_name, MAX_ITEM_PRINT_LEN);
    float price = head->price;
    // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
    sprintf(str, "%d * %s @ $%.2f ea", quantity, item_name, price);
    return EXIT_SUCCESS;
}
