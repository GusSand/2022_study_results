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
    FILE* fd;
    
    // bug 1: missing check for filename == NULL
    fd = fopen(filename, "r");

    if (!fd) {
        return EXIT_FAILURE;
    }

    // bug 2: potential buffer overflow if line is longer than 2048 chars
    char* curr_line = malloc(2048*sizeof(char));
    unsigned int i = 1;
    unsigned int n = 0;
    char* delim = ",";
    int c;
    
    while ((c = fgetc(fd)) != EOF) {
        if (c == '\n') {
            curr_line[n] = '\0';
            n = 0;

            char* arr[3];
            // bug 3: missing check for strtok returning NULL
            arr[0] = strtok(curr_line, delim);
            arr[1] = strtok(NULL, delim);
            arr[2] = strtok(NULL, delim);

            // bug 4: missing check of return status for list_add_item_at_pos
            ref_list_add_item_at_pos(head, arr[0],
                atof(arr[1]), atoi(arr[2]), i++);
            curr_line[0] = '\0';
        } else {
            curr_line[n++] = (char)c;
        }
    }

    free(curr_line);
    fclose(fd);
    return EXIT_SUCCESS;
}
