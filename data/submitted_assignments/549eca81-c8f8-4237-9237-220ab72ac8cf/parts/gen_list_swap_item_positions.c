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
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(pos1 == pos2){return EXIT_SUCCESS;}
    if(pos1 > pos2){int t = pos1; pos1=pos2; pos2=t;}
    if(pos1 < 1){return EXIT_FAILURE;}
    node *p1;
    node *p2;

    // bug 1: missing check for head == NULL
    node *curr = *head;
    for(int i = 1; i < pos2-1; i++){
        if (curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    p2 = curr;
    if(pos1 == 1){
        p2->next = *head;
        *head = p2;
        
    }
 
 
    curr = *head;
    for(int i = 2; i < pos1-1; i++){
        if (curr == NULL){
            return EXIT_FAILURE;
        }
        curr = curr->next;
    }
    p1 = curr;



    //if(p2->next == NULL){return EXIT_FAILURE;}
    
    if(pos2-pos1 == 1){
        // bug 2: missing check for next == NULL
        node *t = p2->next->next;
        p1->next = p2->next;
        p2->next->next = p2;
        p2->next = t;
    }
    else{
        // bug 3: missing check for next == NULL
        node *t = p1->next;
        p1->next = p2->next;
        p2->next = t;
        t = p1->next->next;
        p1->next->next = p2->next->next;
        p2->next->next = t;
    }
    // bug 4: memory leak (loses nodes)
    // bug 5: infinite loop

    return EXIT_SUCCESS;
}
