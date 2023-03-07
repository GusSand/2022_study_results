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
    // bug 1: missing check for str == NULL
    // bug 2: does not check if a item_name is NULL before print
    int status = EXIT_SUCCESS;
    if (head == NULL)
    {
        status = EXIT_FAILURE;
    }
    else
    {
        if (head->next == NULL)
        {
            // bug 3: Use of sprintf instead of snprintf for str with MAX_LEN
            sprintf(str, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);
        }
        else
        {
            // bug 4: Use of sprintf instead of snprintf for str with MAX_LEN
            // bug 5: type confusion, list_item_to_string does not return a string
            sprintf(str, "%d * %s @ $%.2f ea, %s", head->quantity, head->item_name, head->price, list_item_to_string(head->next, str));
        }
    }
    return status;
}
