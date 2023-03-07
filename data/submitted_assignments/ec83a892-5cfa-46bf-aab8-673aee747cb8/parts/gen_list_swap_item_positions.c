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
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    if ((head == NULL) || (*head == NULL) || (pos1 == 0) || (pos2 == 0)) {
        return EXIT_FAILURE;
    }
    if (pos1 == pos2) {
        return EXIT_SUCCESS;
    } else if (pos1 > pos2) {
        int temp = pos1;
        pos1 = pos2;
        pos2 = temp;
    }
    int i = 1;
    node *current = *head;
    while (i < pos1 && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    node *item1 = current;
    while (i < pos2 && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        return EXIT_FAILURE;
    }
    node *item2 = current;
    int temp_quantity = item1->quantity;
    float temp_price = item1->price;
    char *temp_item_name = item1->item_name;
    item1->quantity = item2->quantity;
    item1->price = item2->price;
    item1->item_name = item2->item_name;
    item2->quantity = temp_quantity;
    item2->price = temp_price;
    item2->item_name = temp_item_name;
    return EXIT_SUCCESS;
}
