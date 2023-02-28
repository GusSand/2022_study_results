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
int list_load(node **head, char *filename)
{
    // TODO: Implement this function, 
    // return EXIT_SUCCESS or EXIT_FAILURE when appropriate
    // bug 1: missing check for filename == NULL
    FILE *fptr;
    fptr = fopen(filename, "r");

    if (fptr == NULL){
        return EXIT_FAILURE;
    }

    node* curr = NULL;
    
    int n=1;
    // while (fscanf(fptr, "%20[^,],%f[^,],%d", item_name, &price, &quantity) == 3){
    char line[256];

    while(fgets(line, 256, fptr)){
    // while (fscanf(fptr, "%20[^,],%20[^,],%d", item_name, price, &quantity) == 3){
    // while (fgets(line, sizeof(line), fptr)) {
    // while ((token = strsep(&str, ",")))
        // char *item_name = strtok(line, ",");
        // float price = atof(strtok(NULL, ","));
        // int quantity = atoi(strtok(NULL, ","));

        char* line1 = strdup(line);

        node* newnode = malloc(sizeof(node));
        newnode->item_name = (char*) strtok(line1, ",");
        // bug 2: strtok can return NULL
        newnode->price = atof(strtok(NULL, ","));
        newnode->quantity = atoi(strtok(NULL, ","));
        newnode->next = NULL;

        if(n==1){
            curr = newnode;
            *head = curr;
        }

        else{
            curr->next = newnode;
            curr = curr->next;
        }

        n += 1;
        // newnode->next= curr->next;
    }

    fclose(fptr);

    return EXIT_SUCCESS;
}

