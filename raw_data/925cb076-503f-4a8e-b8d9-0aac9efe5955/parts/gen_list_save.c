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
// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function,
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for filename == NULL
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file");
        return EXIT_FAILURE;
    }

    node* curr = head;
    while (curr != NULL) {
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(file, "%s,%f,%d\n", curr->item_name, curr->price, curr->quantity);
        curr = curr->next;
    }

    fclose(file);

    return EXIT_SUCCESS;
}
