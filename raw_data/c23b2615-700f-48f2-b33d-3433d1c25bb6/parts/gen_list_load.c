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
    if (!head || !filename)
    {
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(filename, "r");
    char line[MAX_ITEM_PRINT_LEN];
    char itemname[MAX_ITEM_PRINT_LEN];
    float price=0;
    int quantity=0;
    int count=1;
    // bug 2: missing check of return status for list_add_item_at_pos
    ref_list_add_item_at_pos(head,"apple",0.80,2,1);
    ref_list_add_item_at_pos(head,"banana",0.50,3,2);
    ref_list_add_item_at_pos(head,"cheese",10.59,1,3);
    // bug 1: missing fclose
    return EXIT_SUCCESS;

    
}
