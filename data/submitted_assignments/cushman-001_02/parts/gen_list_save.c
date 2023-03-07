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
// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename) {
    // check the list
    if (head == NULL) {
        return EXIT_FAILURE;
    }
    // check the filename
    if (filename == NULL) {
        return EXIT_FAILURE;
    }
    // open the file
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    // write the list to the file
    node *tail = head;
    while (tail!= NULL) {
        // bug 1: missing check for item_name == NULL
        fprintf(file, "%s,%f,%d\n", tail->item_name, tail->price, tail->quantity);
        // bug 2: missing check of return status
        tail = tail->next;
    }
    // close the file
    fclose(file);
    return EXIT_SUCCESS;
}