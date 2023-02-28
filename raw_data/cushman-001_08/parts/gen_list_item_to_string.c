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
// print a single list item to an externally allocated string
// This should be in the format of:
// "quantity * item_name @ $price ea", where item_name is a string and 
// price is a float formatted with 2 decimal places.
int list_item_to_string(node *head, char *str) {
    char item_name[MAX_ITEM_PRINT_LEN];
    char price[MAX_ITEM_PRINT_LEN];
    char quantity[MAX_ITEM_PRINT_LEN];
    char *ret_str;
    int num_char;
    
    if (head == NULL) return EXIT_FAILURE;
    
    // extract the item name
    ret_str = strstr(head->item_name, " ");
    if (ret_str == NULL) return EXIT_FAILURE;
    
    num_char = ret_str - head->item_name;
    if (num_char >= MAX_ITEM_PRINT_LEN) return EXIT_FAILURE;
    
    strncpy(item_name, head->item_name, num_char);
    item_name[num_char] = '\0';
    
    // extract the price
    sprintf(price, "%.2f", head->price);
    
    // extract the quantity
    sprintf(quantity, "%d", head->quantity);
    
    sprintf(str, "%s %s @ $%s ea", quantity, item_name, price);
    
    return EXIT_SUCCESS;
}
