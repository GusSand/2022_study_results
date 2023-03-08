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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    // bug 1: missing check for filename == NULL
    FILE *fptr = fopen(filename, "r");
    // bug 2: missing check for fopen failure
    char buf [100];
    int pos = 1;
    while(fgets(buf, 100, fptr) != NULL){
        char t[100];
        strcpy(t,buf);
        char *pt;
        pt = strtok(t, ",");
        char *name = pt;
        // bug 3: missing check for strtok returning NULL causes undefined behavior (pt == NULL)
        pt = strtok(t, ",");
        float price = atof(pt);
        pt = strtok(t, ",\n");
        int quantity = atoi(pt);

        // bug 4: missing check of return status for list_add_item_at_pos
        ref_list_add_item_at_pos(head, name, price, quantity, pos);
        pos ++;
    }

    // bug 5: fails to fclose

    return EXIT_SUCCESS;
}
