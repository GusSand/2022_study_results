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
int list_load(node **head, char *filename) {
    if (filename == NULL) {
        return EXIT_FAILURE;
    }
    // bug 1: missing check for head == NULL
    node *current = *head;
    if ((current != NULL) && (current->next != NULL)) {
        current = current->next;
    }
    FILE *ptr = fopen(filename, "r");
    // bug 2: missing check for fopen failure
    char line[MAX_ITEM_PRINT_LEN];
    while (fgets(line, sizeof(line), ptr)) {
        line[strcspn(line, "\n")] = 0;
        node *newNode = (node*)malloc(sizeof(node));
        // bug 3: strtok returning NULL can cause undefined behavior
        newNode->item_name = strdup(strtok(line, ","));
        newNode->price = atof(strtok(NULL, ","));
        newNode->quantity = atoi(strtok(NULL, ","));
        newNode->next = NULL;
        if (*head == NULL) {
            *head = newNode;
            current = *head;
        } else {
            current->next = newNode;
            current = current->next;
        }
    }
    fclose(ptr);
    return EXIT_SUCCESS;
}
