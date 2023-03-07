#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
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
// add a new item to the list
int list_add(node **head, int quantity, char *item_name, float price) {
    node* cur;
    // bug 4: missing check for head == NULL
    for (cur = *head; cur; cur = cur->next) {} 
    node* new = (node*) malloc(sizeof(node));
    new->quantity = quantity;
    // bug 5: didn't initialize new->item_name
    strcpy(new->item_name, item_name);
    // new->item_name = item_name;
    new->price = price;
    new->next = NULL;
    if (cur == NULL) {
        *head = new;
    }
    else {
        cur->next = new;
    }
    return EXIT_SUCCESS;
}
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // bug 1: missing check for filename == NULL
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) {
        return EXIT_FAILURE;
    }
    // bug 2: failed to initialize quantity, item_name, price
    int* quantity;
    char* item_name;
    float* price;
    // bug 3: fscanf may not set all values
    while (fscanf(fptr, "%s,%f,%d\n", item_name, price, quantity) > 0) {
        list_add(head, *quantity,item_name, *price);
    }
    fclose(fptr);
    return EXIT_SUCCESS;
}
