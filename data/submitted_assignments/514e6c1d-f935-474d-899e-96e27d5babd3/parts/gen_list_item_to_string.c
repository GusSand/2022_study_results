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
    // see the following for the format you need to implement:

    // was fighting the language model whenever I was trying
    // to do anything and I ended up giving up, because whenever
    // I would start with an idea, it would suggest something that 
    // looked good at first sight, I would add it to my own code
    // and then I would spend time debugging some of its code rather
    // than develop my ideas

    // for the other functions where it gave me the answer straight
    // up and it just worked, I felt like I just cheated and got
    // someone else to do the work for me

    // I ended up not having too much time to finish and the couple
    // hours I spent on this was mostly just fighting with the robot
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: missing return
    else {}
}
