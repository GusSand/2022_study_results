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
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        if (filename == NULL) {
            return EXIT_FAILURE;
        } else {
            FILE *f = fopen(filename, "r");
            if (f == NULL) {
                return EXIT_FAILURE;
            } else {
                char *line = malloc(MAX_ITEM_PRINT_LEN);
                if (line == NULL) {
                    return EXIT_FAILURE;
                }
                while (fgets(line, MAX_ITEM_PRINT_LEN, f)) {
                    char *item_name = strtok(line, ",");
                    char *price = strtok(NULL, ",");
                    char *quantity = strtok(NULL, ",");
                    float f_price = atof(price);
                    int i_quantity = atoi(quantity);
                    ref_list_add_item_at_pos(head, item_name, f_price, i_quantity, 0);
                }
                free(line);
                fclose(f);
                return EXIT_SUCCESS;
            }
        }
    }
}
