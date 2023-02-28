#include <stdio.h> 
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>
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
// save the list to file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
int list_save(node *head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    if(head ==NULL){
        return EXIT_SUCCESS;
    }
    node *temp = head;
    // bug 1: type confusion char* vs char
    int fd  = open(*filename,  1);
    if(fd<0){
        return EXIT_FAILURE;
    } else{
    char* str;
        while(temp!=NULL){
            str = "%s,%.2f,%d\n", temp->item_name, temp->price, temp->quantity;
            // bug 3: char ** vs char* confusion
            // bug 4: sizeof pointer
            // bug 5: missing check for write failure
            write(fd,&str, sizeof(str));
        }
    }
    // bug 2: missing close() leaks file descriptor
    
    return EXIT_SUCCESS;
}
