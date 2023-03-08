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
    // bug 1: missing check for filename == NULL
    FILE *f = fopen(filename, "r");
    if (f == NULL){
        return EXIT_FAILURE;
    }
    // bug 2: buffer overflow fixed size buffer
    char item_name[100];
    float price;
    int quantity;
    int l =0;
    while(!feof(f)){
        // bug 3: fscanf may not set all values
        // bug 4: failure to check fscanf return value
        fscanf(f, "%[^,],%f,%d\n", item_name, &price, &quantity);
        // bug 5: missing check of return status for list_add_item_at_pos
        ref_list_add_item_at_pos(head, item_name, price, quantity, l);
        l+=1;
    }
    fclose(f);
    return EXIT_SUCCESS;
}
