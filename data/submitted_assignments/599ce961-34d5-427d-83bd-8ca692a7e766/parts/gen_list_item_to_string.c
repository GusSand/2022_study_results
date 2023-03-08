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
    // bug 1: missing check for str == NULL
    if (head == NULL){
        return EXIT_FAILURE;
    }
    printf("SOmething");
    // bug 2: type confusion: mixing up char* and char
    char* quan = head->quantity + '0';
    strcat(str, quan);
    strcat(str, " * ");
    // bug 3: does not check if a item_name is NULL
    strcat(str, head->item_name);
    strcat(str, " @ $");
    char *buf;
    // bug 4: failure to initialize buf
    gcvt(head->price, 4, buf);
    strcat(str, buf);
    strcat(str, " ea");
    printf("%s", str);
    // bug 5: doesn't check that length < MAX_ITEM_PRINT_LEN
    return EXIT_SUCCESS;
}
