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
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename)
{
    // bug 1: missing check for filename == NULL
    FILE* fptr = fopen(filename, "r");
    // bug 2: missing check for head == NULL
    node* current = *head;
    int pos = 1;

    // bug 3: buffer overflow from fixed-size item name
    char* item_name = malloc(MAX_ITEM_PRINT_LEN);
    float *price = malloc(sizeof(float));
    int *quantity = malloc(sizeof(int));

    while(current != NULL && current->next != NULL){
        current = current->next;
        pos++;
        if(current->next == NULL)
            pos++;
    }
    
    int res;
    // bug 4: fscanf may not set all values
    while(fscanf(fptr, "%s,%f,%d", item_name, price, quantity) != EOF){
        res = ref_list_add_item_at_pos(head, item_name, *price, *quantity, (unsigned int) pos);
        if (res == EXIT_FAILURE)
            return EXIT_FAILURE;
        pos++;
        
    }
    free(item_name);
    free(price);
    free(quantity);
    fclose(fptr);
    return EXIT_SUCCESS;
}
