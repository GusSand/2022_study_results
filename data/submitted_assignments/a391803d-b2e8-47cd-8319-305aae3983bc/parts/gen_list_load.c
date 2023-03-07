#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "list.h"

// NOTE: I was unable to test this file according to the instructions in
// README.md!

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
    // bug 1: missing check for head == NULL
    node *curr = *head;
    node *prev = NULL;
    // bug 2: missing check for filename == NULL
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening the file %s\n", filename);
        return EXIT_FAILURE;
    }
    // go to the end of the list
    if (curr == NULL) {
        printf("Need to pass in a singly linked list!\n");
        return EXIT_FAILURE;    // need to pass in a singly linked list!
    }
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }
    curr = prev;    // last item of list
    // bug 3: use of uninitialized item_name
    char *item_name;
    float price;
    int quantity;
    // read the lines and load the nodes at the end of the list
    // bug 4: fscanf may not initialize price, quantity
    while (fscanf(fp, "%s,%.2f,%i\n", item_name, price, quantity) != EOF) {
        node *newNode = (node *)malloc(sizeof(node));
        // bug 5: use of uninitialized newNode->item_name
        sprintf(newNode->item_name, "%s", item_name);
        newNode->price = price;
        newNode->quantity = quantity;
        newNode->next = NULL;
        curr->next = newNode;
        curr = curr->next;
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
