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
    FILE * file;
    // bug 1: missing check for filename == NULL
    file = fopen(filename, "r");
    if (file == NULL) return EXIT_FAILURE;
    // bug 2: missing check for head == NULL
    node * cur = *head;
    if (cur == NULL) return EXIT_FAILURE;
    while (cur->next != NULL) cur = cur->next;
    // bug 3: failure to initialize new_name
    char * new_name; int new_price; int new_quant;
    // bug 4: fscanf may not initialize all values
    while (fscanf(file, "%s,%d,%d\n", new_name, &new_price, &new_quant) > 0) {
        node * new = malloc(sizeof(node));
        // bug 5: missing strdup
        new->item_name = new_name;
        new->price = new_price;
        new->quantity = new_quant;
        cur->next = new;
        new->next = NULL;
        cur = cur->next;
        if (cur == NULL) return EXIT_FAILURE;
    }
    if (fscanf(file, "%s,%d,%d\n", new_name, &new_price, &new_quant) < 0) return EXIT_FAILURE;
    // bug 6: leaks file descriptor on EXIT_FAILURE
    fclose(file);
    return EXIT_SUCCESS;
}
