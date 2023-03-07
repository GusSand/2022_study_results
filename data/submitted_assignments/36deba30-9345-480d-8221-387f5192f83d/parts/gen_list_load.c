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
// item_name, price, quantity\n
// one item per line, separated by commas and new line at the end
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // TODO: Implement this 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    int pos = 1;
    // bug 1: missing check for head == NULL
    while(*head !=NULL){
        pos++;
        *head = (*head)->next;
    }
    // bug 2: missing check for filename == NULL
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return EXIT_FAILURE;
    }
    // bug 3: buffer overflow
    char *item_name = (char *) malloc(sizeof(char)*256);
    float price;
    int quantity;
    // bug 4: fscanf may not initialize all values
    while (fscanf(fp, "%s,%f,%d\n", item_name, &price, &quantity)!= EOF){
        // bug 5: missing check of return status for list_add_item_at_pos
        ref_list_add_item_at_pos(&(*head), item_name, price, quantity, pos);
        pos++;
    }
    // bug 6: memory leak failing to free item_name
    return EXIT_SUCCESS;
}
