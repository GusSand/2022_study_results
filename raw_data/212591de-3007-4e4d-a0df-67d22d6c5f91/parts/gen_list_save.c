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
    FILE* ptr;
    // bug 1: missing check for filename == NULL
    ptr = fopen(filename, "w");
    char str[MAX_ITEM_PRINT_LEN];
    if (ptr == NULL) {
        return EXIT_FAILURE;
    }
    while (head != NULL) {
        ref_list_item_to_string(head, str);
        // bug 2: missing check for fprintf failure
        // bug 3: missing check for item_name == NULL
        fprintf(ptr, "%s,%.2f,%d\n", head->item_name, head->price, head->quantity);
        head = head->next;
    }
    fclose(ptr);
    return EXIT_FAILURE;
}
