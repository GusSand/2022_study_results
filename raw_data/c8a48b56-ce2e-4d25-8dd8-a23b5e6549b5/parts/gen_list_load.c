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
    node* cur;
    // bug 1: missing check for head == NULL
    cur = *head;
    while(cur != NULL){
        cur = cur->next;
    }

    FILE *file;
    // bug 2: missing check for filename == NULL
    file = fopen(filename, "w");
    while(cur != NULL){
        // bug 3: potential buffer overflow on cur->item_name
        fscanf(file, "%d,%s,%f", &cur->quantity, cur->item_name, &cur->price);
        cur = cur->next;
    }
    // bug 4: fails to call fclose
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
