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
    int result = EXIT_SUCCESS;

    if (head == NULL) {
        strcpy(str, "The list is empty.");
    } else {
        int item_name_len = strlen(head->item_name);
        int price_len = snprintf(NULL, 0, "%.2f", head->price);
        int quantity_len = snprintf(NULL, 0, "%d", head->quantity);
        int total_len = item_name_len + price_len + quantity_len + 12;

        if (total_len > MAX_ITEM_PRINT_LEN) {
            result = EXIT_FAILURE;
            strcpy(str, "The item name is too long.");
        } else {
            int printed = snprintf(str, total_len, "%d * %s @ $%.2f ea", head->quantity, head->item_name, head->price);

            if (printed != total_len) {
                result = EXIT_FAILURE;
                strcpy(str, "The string was not filled completely.");
            }
        }
    }

    return result;
}
