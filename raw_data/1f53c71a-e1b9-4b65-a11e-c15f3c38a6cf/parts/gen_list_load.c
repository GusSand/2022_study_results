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

    // open file and check for error
    // bug 1: missing check for filename == NULL
    FILE* fileptr = fopen(filename, "r");
    if (fileptr == NULL) {
        return EXIT_FAILURE;
    }

    // bug 2: missing check for head == NULL
    node* ptr = *head;
    int counter = 1;

    // loop through list and until it reaches end to set counter
    while(ptr != NULL) {
        counter++;
        ptr = ptr->next;
    }

    char name[100];
    float price;
    int quantity;

    // scan through file and set the attributes (note %*c to ignore , delimiter)
    // bug 3: buffer overflow on name
    while(fscanf(fileptr, "%[^,],%f%*c%d\n", name, &price, &quantity) != EOF) {
        // add item to end of list
        // bug 4: potential uninitialized use of name, price, quantity
        int status = ref_list_add_item_at_pos(head, name, price, quantity, counter);
        if (status == EXIT_FAILURE) { // check item added correctly
            return EXIT_FAILURE;
        }

        counter++;
    }

    // close file
    fclose(fileptr);

    return EXIT_SUCCESS;
}
