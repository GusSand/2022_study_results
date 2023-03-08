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
    // bug 1: missing check for head == NULL
    node* cur = *head;
    node* prev = cur;
    
    // bug 2: potential buffer overflow if list is longer than 10000
    const char* item_list[10000];
    int flag=0;

    int i=0;
    while (1){
        if(cur == NULL){
            break;
        }
        else{
            item_list[i] = cur->item_name;

        }
        for (int j=0; j<i; j++){
            // bug 3: use of uninitialized variable
            if (cur->item_name == item_list[j]){
                flag=1;
            }
        }
        if(flag){
            //prev unchanged
            cur = cur->next;           
            i++;
        }
        else{
            prev = cur;
            cur = cur->next;
            i++;
        }

    }
    // bug 4: missing check for cursor NULL
    node* fut = cur->next;

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_FAILURE;
}
