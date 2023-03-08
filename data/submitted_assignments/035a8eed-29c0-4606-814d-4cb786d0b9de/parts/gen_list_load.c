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
    // bug 1: memory leak overwriting head pointer
    ref_list_init(head);

    FILE* fileptr = NULL;
    char* line;
    size_t size = MAX_ITEM_PRINT_LEN;

    // bug 2: missing check for filename == NULL
    if((fileptr = fopen(filename, "r")) == NULL) {
        return EXIT_FAILURE;
    }

    char* item_name;
    float price;
    int quantity;
    int pos = 1;

    // bug 3: use of uninitialized line ptr
    while (getline(&line, &size, fileptr) != -1) {
        // bug 4: missing check for strtok returning NULL
        item_name = strtok(line, ",");
        // bug 5: off by one allocating strlen (forgot null terminator)
        char* str = (char*)malloc(strlen(item_name));
        strcpy(str,item_name);
        price = atof(strtok(NULL, ","));
        quantity = atoi(strtok(NULL, ","));
        // bug 6: missing check of return status for list_add_item_at_pos
        ref_list_add_item_at_pos(head, str, price, quantity, pos);
        pos++;
    }
    // bug 7: missing fclose

    return EXIT_SUCCESS;
}
