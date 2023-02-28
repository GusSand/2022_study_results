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
// helper function
char* memRealloc(char* buffer, int oldSize, int newSize) {
    char* newBuffer = malloc(newSize);
    // bug 6: buffer overflow if oldSize > newSize
    for(int i = 0; i < oldSize; i++)
        newBuffer[i] = buffer[i];
    // bug 4: memory leak failing to free buffer
    return newBuffer;
}
// load the list from file filename
// the file should be in the following format:
// item_name,price,quantity\n 
//   (one item per line, separated by commas, and newline at the end)
// the loaded values are added to the end of the list
int list_load(node **head, char *filename) {
    // bug 1: missing check for head == NULL
    // bug 2: memory leak overwriting head pointer 
    *head = NULL; 

    // bug 3: missing check for filename == NULL
    FILE* f = fopen(filename, "r");
    if(f == NULL) {
        return EXIT_FAILURE;
    }
    
    int bufSize = 5;
    int bytesRead = 0;

    char* buf = malloc(bufSize);
    int res = fread(buf, 1, bufSize, f);
    bytesRead += res;

    while(res > 0) {
        if(bytesRead == bufSize) {
            int oldSize = bufSize;
            bufSize *= 2;
            buf = memRealloc(buf, oldSize, bufSize);
        }

        res = fread(buf+bytesRead, 1, bufSize-bytesRead, f);
        bytesRead += res;
    }   

    int state = 0;
    int start = 0;
    int end = 0;
    int strSize = 20;
    int pos = 1;
    char* str = malloc(strSize);
    char* item_name;
    float price;
    int quantity = 0;
    for(int i = 0; i < bytesRead; i++) {
        if(buf[i] == ',' || buf[i] == '\n') {
            end = i;
            int newSize = end-start;

            if(i + 1 == bytesRead) newSize += 1;

            str = memRealloc(str, strSize, newSize);
            memmove(str, buf+start, newSize);
            // bug 5: does not ensure str is null-terminated
            strSize = newSize;
            start = end+1;

            if(state == 0) {
                item_name = str;
                state = 1;
            } else if(state == 1) {
                price = atof(str);
                state = 2;
            } else if(state == 2) {
                quantity = atoi(str);
                // bug 7: missing check of return status for list_add_item_at_pos
                ref_list_add_item_at_pos(head, item_name, price, quantity, pos);
                pos ++ ; 
                state = 0;
            }
        }
    }

    fclose(f);
    free(str);
    free(buf);
    return EXIT_SUCCESS;
}
