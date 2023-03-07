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
// create a new list
int list_init(node **head) {
    // check for NULL pointer
    if (head == NULL) return EXIT_FAILURE;

    // initialize the first node
    *head = (node *)malloc(sizeof(node));
    if (*head == NULL) return EXIT_FAILURE;

    // initialize the first node
    (*head)->item_name = NULL;
    (*head)->price = 0.0;
    (*head)->quantity = 0;
    (*head)->next = NULL;
    return EXIT_SUCCESS;
}
