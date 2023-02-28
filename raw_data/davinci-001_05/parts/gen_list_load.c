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
    // check if node is null
    if (*head == NULL) {
        fprintf(stderr, "list_load: node is null\n");
        return EXIT_FAILURE;
    }

    // check if string is null
    if (filename == NULL) {
        fprintf(stderr, "list_load: filename is null\n");
        return EXIT_FAILURE;
    }

    // set up variables
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp = fopen(filename, "r");
    if (fp == 0) {
        fprintf(stderr, "list_load: fopen failed\n");
        return EXIT_FAILURE;
    }

    // load the list
    while ((read = getline(&line, &len, fp)) != -1) {
        char *item_name = strtok(line, ",");
        float price = atof(strtok(NULL, ","));
        int quantity = atoi(strtok(NULL, "\n"));
        node *new_node = malloc(sizeof(node));
        new_node->item_name = item_name;
        new_node->price = price;
        new_node->quantity = quantity;
        new_node->next = (*head);
        (*head) = new_node;
    }
    free(line);
    fclose(fp);

    return EXIT_SUCCESS;
}
