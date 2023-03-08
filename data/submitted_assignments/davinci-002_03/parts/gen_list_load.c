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
    if (*head == NULL) {
        return EXIT_FAILURE;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return EXIT_FAILURE;
    }
    char line[MAX_ITEM_PRINT_LEN];
    while (fgets(line, MAX_ITEM_PRINT_LEN, file) != NULL) {
        char *item_name = strdup(strtok(line, ","));
        float price = strtof(strtok(NULL, ","), NULL);
        int quantity = strtol(strtok(NULL, ","), NULL, 10);
        ref_list_add_item_at_pos(head, item_name, price, quantity, -1);
    }
    fclose(file);
    return EXIT_SUCCESS;
}
