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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename){
    node* curr;
    curr = *head;
    node* prev;
    prev = *head;
    FILE *fptr;
    // bug 1: missing check for head == NULL
    // bug 2: missing check for filename == NULL
    fptr = fopen(filename, "r");
    // bug 3: missing check for fopen failure
    float val;
    int quant;
    int pos = 1;
    while(curr != NULL) {
        prev = curr;
        curr=curr->next;
        pos++;
    }
    while(!feof(fptr)){
        // bug 4: buffer overflow fixed size buffer
        char* name = (char*) malloc(100 * sizeof(char));
        // bug 5: fscanf can fail to set all arguments
        fscanf(fptr,"%[^,],%f,%d ", name, &val, &quant);
        // bug 6: missing check of return status for list_add_item_at_pos
        ref_list_add_item_at_pos(head, name, val, quant, pos);
        pos++;
        // bug 7: memory leak failing to free name
    }
    
    fclose(fptr);
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    return EXIT_SUCCESS;
}
