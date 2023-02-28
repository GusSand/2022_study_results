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
node* get_item_at_pos(node** head, int pos) {
    node* curr = *head;
    int i = 1;
    while (curr != NULL) {
        if (i == pos) {
            return curr;
        }
        curr = curr->next;
        i++;
    }
    return NULL;
}
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    int capacity = 128;
    char** item_names = malloc(capacity*sizeof(char*));
    
    // bug 1: missing check for head == NULL
    node *curr = *head;
    int pos = 1;

    while (curr) {
        if (pos >= capacity) {
            capacity *= 2;
            item_names = realloc(item_names, capacity*sizeof(char*));
        }

        int found = 0;

        for (unsigned int i = 0; i < pos - 1 && !found; ++i) {
            // bug 2: missing check for item_name == NULL
            // bug 3: potential use of uninitialized variable
            if (strcmp(curr->item_name, item_names[i]) == 0) {
                node* to_update = get_item_at_pos(head, i+1);
                // bug 4: use after free
                ref_list_update_item_at_pos(head,
                    to_update->item_name,
                    to_update->price,
                    to_update->quantity + curr->quantity,
                    i+1);
                
                curr = curr->next;
                // bug 5: missing check of return status for remove_item_at_pos
                ref_list_remove_item_at_pos(head, pos);
                found = 1;
            }
        }

        if (!found) {
            item_names[pos-1] = curr->item_name;
            pos++;
            curr = curr->next;
        }
    }

    return EXIT_SUCCESS;
}
