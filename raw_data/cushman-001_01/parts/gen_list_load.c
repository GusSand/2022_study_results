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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // bug 3: missing check for filename == NULL
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: list_load\n");
        return EXIT_FAILURE;
    }
    char line[200];
    char *token;
    while (fgets(line, 200, fp) != NULL) {
        int len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        token = strtok(line, ",");
        char *item_name = token;
        token = strtok(NULL, ",");
        // bug 2: undefined behavior if token == NULL
        float price = atof(token);
        token = strtok(NULL, ",");
        int quantity = atoi(token);
        ref_list_add_item_at_pos(head, item_name, price, quantity, 0);
        // bug 1: missing check of return status
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
