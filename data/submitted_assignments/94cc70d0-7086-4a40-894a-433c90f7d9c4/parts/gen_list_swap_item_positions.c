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
//  or EXIT_SUCCESS to indicate whether the operation was 

#include "reflist.h"
// swap the item at position pos1 with the item at position pos2
int list_swap_item_positions(node **head, int pos1, int pos2) {
    // bug 1: missing check for head == NULL
    // bug 2: missing check for *head == NULL
    node* current = *head;
    int current_pos = 1;
    while(current_pos < pos1){
        // bug 3: missing check for next == NULL
        current = current->next;
        current_pos++;
    }

    char* temp_item_name = current->item_name;
    float temp_price = current->price;
    int temp_quantity = current->quantity;

    current_pos = 1;
    current = *head;
    while(current_pos < pos2){
        // bug 4: missing check for next == NULL
        current= current->next;
        current_pos++;
    }

    node* node2 = current;

    int res = ref_list_update_item_at_pos(head, node2->item_name, node2->price, node2->quantity, pos1);
    if(res == EXIT_FAILURE)
        return EXIT_FAILURE;
    res = ref_list_update_item_at_pos(head, temp_item_name, temp_price, temp_quantity, pos2);
    if(res == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
