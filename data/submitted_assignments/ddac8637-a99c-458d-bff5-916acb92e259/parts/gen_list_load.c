#include <stdio.h> 
#include <stdlib.h>
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
int list_load(node **head, char *filename)
{
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for filename == NULL
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        return EXIT_FAILURE;
    }
    char data[MAX_ITEM_PRINT_LEN];
    char* token;
    float num;
    int quantity;
    while(fgets(data, MAX_ITEM_PRINT_LEN, file) != NULL){
        node *newNode = malloc(sizeof(node));
        // bug 2: buffer overflow on data
        // bug 3: newNode->item_name not initialized
        sscanf(data, "%s,%f,%d", newNode->item_name, &num, &quantity);
        newNode->price = num;
        newNode->quantity = quantity;
        newNode->next = NULL;
        // bug 4: missing check for head == NULL
        if(*head == NULL){
            *head = newNode;
        }
        else{
            (*head)->next = newNode;
            // bug 5: memory leak, losing elements of the list
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
