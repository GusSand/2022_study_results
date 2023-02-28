#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
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
// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // bug 1: missing check for filename == NULL
    FILE* fptr = fopen(filename, "w");
    if (fptr == NULL) {
        return EXIT_FAILURE;
    }
    for (; head; head = head->next) {
        // bug 2: missing check for item_name == NULL
        // bug 3: missing check for fprintf failure
        fprintf(fptr, "%s,%f,%d",head->item_name, head->price, head->quantity);
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}
