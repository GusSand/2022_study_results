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
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        if (filename == NULL) {
            return EXIT_FAILURE;
        } else {
            FILE *f = fopen(filename, "w+");
            if (f == NULL) {
                return EXIT_FAILURE;
            } else {
                node *cur = head;
                while (cur != NULL) {
                    fprintf(f, "%s,%.2f,%d\n", cur->item_name, cur->price, cur->quantity);
                    cur = cur->next;
                }
                fclose(f);
                return EXIT_SUCCESS;
            }
        }
    }
}
