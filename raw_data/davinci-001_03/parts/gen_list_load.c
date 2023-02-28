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
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    char line[MAX_ITEM_PRINT_LEN+1];
    while (fgets(line, MAX_ITEM_PRINT_LEN, fp)) {
        int i=0;
        int pos1 = 0, pos2 = 0;
        char *item_name = NULL;
        float price = 0.0;
        int quantity = 0;
        while (line[i]!=',' && line[i]!=0) {
            i++;
        }
        if (line[i]==0) {
            break;
        }
        item_name = line;
        i++;
        while (line[i]!=',' && line[i]!=0) {
            i++;
        }
        if (line[i]==0) {
            break;
        }
        pos1 = i+1;
        float f = atof(&line[i+1]);
        i=0;
        while (line[i]!=0) {
            i++;
        }
        if (line[i]==0) {
            break;
        }
        pos2 = i;
        quantity = atoi(&line[pos1]);
        price = f;
        ref_list_add_item_at_pos(head, item_name, price, quantity, pos2);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
