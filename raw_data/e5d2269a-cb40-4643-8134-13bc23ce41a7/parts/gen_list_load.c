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
    // bug 1: missing check for head == NULL
    node* _head = *head;
    while(_head && _head->next){
        _head = _head->next;
    }
    FILE* fp;
    // bug 2: missing check for filename == NULL
    fp = fopen(filename, "r");

    if(!fp){
        return EXIT_FAILURE;
    }

    char line[100];

    while(fgets(line, 100, fp) != NULL){
        char* tmp;
        node* new_node = (struct _node*) malloc(sizeof(struct _node));
        // bug 3: strtok returning NULL will cause undefined behavior
        tmp = strtok(line,",");
        new_node->item_name = (char*)malloc(strlen(tmp)+1);
        strcpy(new_node->item_name, tmp);

        tmp = strtok(NULL,",");
        new_node->price = atof(tmp);

        tmp = strtok(NULL,",");
        new_node->quantity = atoi(tmp);

        new_node->next = NULL;
        if(_head)
            _head->next = new_node;
        _head = new_node;
        if(*head == NULL){
            *head = new_node;
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}
