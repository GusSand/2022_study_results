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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) 
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for head == NULL

    node* ptr = *head;
    int ptr_counter = 1;

    // loops through each item in list
    while (ptr != NULL) {
        node* dup_ptr = ptr->next; // checks for duplicates
        int dup_counter = ptr_counter + 1;

        // loops through rest of list starting with the node after ptr
        while(dup_ptr != NULL) {
            // update quantity if the two pointers have same item name
            // bug 2: missing check for item_name == NULL
            if(strcmp(ptr->item_name, dup_ptr->item_name) == 0) {
                node* rem_ptr = dup_ptr;
                ptr->quantity += rem_ptr->quantity; // update quantity
                dup_ptr = dup_ptr->next; // move dup_ptr to next pointer

                // remove duplicate and check for error
                int status = ref_list_remove_item_at_pos(head, dup_counter);
                if (status == EXIT_FAILURE) {
                    return EXIT_FAILURE;
                }
                continue;
            }

            dup_ptr = dup_ptr->next;
            dup_counter++;
        }

        ptr = ptr->next;
        ptr_counter++;
    }


    return EXIT_SUCCESS;
}
