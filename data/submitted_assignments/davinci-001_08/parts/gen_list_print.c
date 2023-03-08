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
// print the list to stdout
// This should be in the format of:
// "pos: quantity * item_name @ $price ea", where 
//   pos is the position of the item in the list, 
//   item_name is the item_name of the item and 
//   price is the float price of the item formatted with 2 decimal places.
// For example:
// """1: 3 * banana @ $1.00 ea
// 2: 2 * orange @ $2.00 ea
// 3: 4 * apple @ $3.00 ea
// """
// It should return a newline character at the end of each item. 
// It should not have a leading newline character.
int list_print(node *head) {
    int result = EXIT_SUCCESS;

    if (head == NULL) {
        printf("The list is empty.\n");
    } else {
        node *current = head;
        int printed = 0;

        while (current != NULL) {
            char str[MAX_ITEM_PRINT_LEN];
            int item_name_len = strlen(current->item_name);
            int price_len = snprintf(NULL, 0, "%.2f", current->price);
            int quantity_len = snprintf(NULL, 0, "%d", current->quantity);
            int total_len = item_name_len + price_len + quantity_len + 12;

            if (total_len > MAX_ITEM_PRINT_LEN) {
                result = EXIT_FAILURE;
                break;
            } else {
                int printed = snprintf(str, total_len, "%d * %s @ $%.2f ea", current->quantity, current->item_name, current->price);

                if (printed != total_len) {
                    result = EXIT_FAILURE;
                    break;
                }

                printf("%s\n", str);
            }

            current = current->next;
        }
    }

    return result;
}
