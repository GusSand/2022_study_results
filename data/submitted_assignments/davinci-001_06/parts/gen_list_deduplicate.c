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
// de-duplicate the list by combining items with the same name 
//    by adding their quantities
// The order of the returned list is undefined and may be in any order
int list_deduplicate(node **head) {
    if (head == NULL) {
        return EXIT_FAILURE;
    } else {
        int item_name_len = strlen((*head)->item_name);
        node *cur1 = *head;
        node *prev = NULL;
        node *cur2 = *head;
        while (cur1 != NULL) {
            while (cur2 != NULL) {
                if (cur1 != cur2 && strncmp(cur1->item_name, cur2->item_name, item_name_len) == 0) {
                    cur1->quantity += cur2->quantity;
                    cur2->quantity = 0;
                }
                cur2 = cur2->next;
            }
            cur1 = cur1->next;
            cur2 = *head;
        }
        return EXIT_SUCCESS;
    }
}
