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
    // check if node is null
    if (head == NULL) {
        fprintf(stderr, "list_save: node is null\n");
        return EXIT_FAILURE;
    }

    // check if string is null
    if (filename == NULL) {
        fprintf(stderr, "list_save: filename is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    int pos = 1;
    node *current = head;
    FILE *fp = fopen(filename, "w");
    while (current != NULL) {
        char item_str[MAX_ITEM_PRINT_LEN];
        ref_list_item_to_string(current, item_str);
        fprintf(fp, "%s\n", item_str);

        pos++;
        current = current->next;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
