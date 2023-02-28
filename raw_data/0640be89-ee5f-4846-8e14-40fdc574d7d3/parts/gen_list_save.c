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
// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate

    //Open file using given filename
    // bug 1: missing check for filename == NULL
    FILE * fptr = fopen(filename, "w");

    //check if opened correctly and if list is empty
    // bug 2: leaks file descriptor on EXIT_FAILURE
    if(fptr == NULL || head == NULL)
        return EXIT_FAILURE;

    node * current = head;
    //iterate through and print to file
    while(current != NULL){
        // bug 3: missing check for fprintf failure
        // bug 4: missing check for item_name == NULL
        fprintf(fptr, "%s,%.2f,%d\n", current->item_name, current->price, current->quantity);
        current = current->next;
    }

    fclose(fptr);


    return EXIT_SUCCESS;
}
