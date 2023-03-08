#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
    if (head == NULL || filename == NULL) {
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    node *curr = head;
    while (curr != NULL) {
        int n = fprintf(fp, "%s,%.2f,%d\n", curr->item_name, curr->price, curr->quantity);
        if (n < 0) {
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
