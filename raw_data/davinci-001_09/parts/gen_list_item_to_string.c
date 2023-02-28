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

// Note: All list_ functions return a status code EXIT_FAILURE or EXIT_SUCCESS

#include "reflist.h"
// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    // check for NULL pointer
    if (head == NULL || str == NULL) return EXIT_FAILURE;

    // check for empty list
    if (head->item_name == NULL) return EXIT_SUCCESS;

    // print item_name
    char item_name[MAX_ITEM_PRINT_LEN + 1];
    strncpy(item_name, head->item_name, MAX_ITEM_PRINT_LEN);
    item_name[MAX_ITEM_PRINT_LEN] = '\0';

    // print price
    char price[20];
    sprintf(price, "%.2f", head->price);

    // print quantity
    char quantity[20];
    sprintf(quantity, "%d", head->quantity);

    // print string
    char format[] = "%d * %s @ $%s ea";
    int result = snprintf(str, MAX_ITEM_PRINT_LEN, format, quantity, item_name, price);
    if (result < 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
