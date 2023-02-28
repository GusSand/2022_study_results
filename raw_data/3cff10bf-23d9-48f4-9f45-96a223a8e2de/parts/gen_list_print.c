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
// print the entire list
int list_print(node *head)
{
    // TODO: Implement this 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    node *temp = head;
    while (temp != NULL) {
        char item[MAX_ITEM_PRINT_LEN];
        // bug 1: doesn't check return value of list_item_to_string
        ref_list_item_to_string(temp, item);
        // bug 2: maybe uninit item
        printf("%s\n", item);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}
