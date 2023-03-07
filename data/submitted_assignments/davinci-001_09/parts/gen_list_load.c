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
    // check for NULL pointer
    if (head == NULL || filename == NULL) return EXIT_FAILURE;

    // check for empty list
    if (*head == NULL || (*head)->item_name == NULL) return EXIT_SUCCESS;

    FILE *file = fopen(filename, "r");
    if (file == NULL) return EXIT_FAILURE;

    // load list from file
    node *current = *head;
    while (fscanf(file, "%s,%f,%d", current->item_name, &current->price, &current->quantity) != EOF) {
        current->next = (node *)malloc(sizeof(node));
        if (current->next == NULL) return EXIT_FAILURE;
        current = current->next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}