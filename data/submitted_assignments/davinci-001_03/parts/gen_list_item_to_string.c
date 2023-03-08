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
    node *current = head;
    int i=0, j=0;
    char *p = str;
    while (current!=NULL) {
        int len=0;
        float f = current->price;
        char *item_name = current->item_name;
        len = sprintf(p, "%d * %s @ $%.2f ea", current->quantity, item_name, f);
        p += len;
        i++;
        current = current->next;
        j++;
    }
    return EXIT_SUCCESS;
}
