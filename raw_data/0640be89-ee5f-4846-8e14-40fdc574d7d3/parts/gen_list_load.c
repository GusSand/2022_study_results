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
    //Open file using given filename
    // bug 1: missing check for filename == NULL
    FILE * fptr = fopen(filename, "r");

    //check if opened correctly
    if(fptr == NULL)
        return EXIT_FAILURE;

    // bug 2: memory leak overwriting head ptr
    ref_list_init(head);
    char * line;
    char * name;
    char * price;
    char * quantity;
    unsigned int pos = 1;
    // bug 3: use of uninitialized char * line
    while(fgets(line, 100, fptr) != NULL){
        // bug 4: fail to check if strtok returns NULL
        name = strtok(line, ",");
        price = strtok(NULL, ",");
        quantity = strtok(NULL, ",");
        // bug 5: missing check of return status for list_add_item_at_pos
        ref_list_add_item_at_pos(head, name, strtof(price, NULL), atoi(quantity), pos);
        pos = pos + 1;
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}
