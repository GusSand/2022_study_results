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
int list_deduplicate(node **head) {
    node* p1;
    node* p2;
    node* dup;
    int pos = 1;
    int pos1 = 1;
    // bug 1: missing check for head == NULL
    p1 = *head;
    while(p1 != NULL && p1->next != NULL) {
        p2 = p1;
        pos = pos1;
        while(p2 != NULL && p2->next != NULL) {
            // bug 2: missing check for item_name == NULL
            if(!strcmp(p1->item_name,p2->next->item_name)) {

                dup = p2->next;
                int sum = p1->quantity + p2->next->quantity;
                p1->quantity = p1->quantity + p2->next->quantity;


                if(dup->next == NULL){
                    p2->next=NULL;
                    break;
                }
                else {
                    p2->next=p2->next->next;
                }

                // bug 3: missing free of item_name
                free(dup);
                break;
                
            }
            else{
                p2=p2->next;
                pos++;
            }

        }
        if(p1->next==NULL) {
            break;
        }
        else {
            p1=p1->next;
        }
        pos1++;
    }

    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
